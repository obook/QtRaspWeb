/*
$Id: mainwindow.cpp 33 2020-02-15 09:38:15Z obooklage $
$Revision: 33 $
$Author: obooklage $
$HeadURL: https://svn1.mecavideofrance.com/SVN/DEV/com.obooklage.pi4.admoovqt/src/mainwindow.cpp $
$Date: 2020-02-15 10:38:15 +0100 (sam. 15 févr. 2020) $
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Configuration */

    loadConfig();

    const QStringList args = QCoreApplication::arguments();
    if(args.count() > 1)
    {
        CURRENT_URL = args[1];
    }

    /* Web browser */

    view = new QWebEngineView(this);
    setCentralWidget(view);
    QObject::connect(view->page(), SIGNAL(loadFinished(bool)), this, SLOT(finishedLoadNotification(bool)));

    /* FullScreen */

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    QTimer::singleShot(0, this, SLOT(showFullScreen()));

    /* Keyboard */

    QShortcut *shortcut_close = new QShortcut(QKeySequence("Esc"), this);
    QObject::connect(shortcut_close, SIGNAL(activated()), this, SLOT(close()));

    /* Mouse
    connect( this, SIGNAL( mousePressEvent(QMouseEvent*) ), this, SLOT( close() ) );
 */

    /* Attendre un peu */

    delay(5);

    /* Timer */

    timewait = 1800000;  /* 30 minutes */

    timer = new QTimer();
    timer->connect( timer, SIGNAL(timeout()), this, SLOT(RefreshScreen()));
    timer->setInterval(timewait);
    timer->start();

    /* Atteindre l'URL */

    RefreshScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RefreshScreen()
{
    view->load(QUrl(CURRENT_URL));

    /* Cacher la souris */

    // this->setCursor(Qt::BlankCursor);
    QCursor cursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);
}

void MainWindow::delay(int sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::loadConfig()
{
    QString configPath = QCoreApplication::applicationDirPath() + "/ADMoovQt.json";
    QFile file(configPath);

    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        CURRENT_URL = doc.object().value("URL").toString();
    } else {
        CURRENT_URL = "https://www.google.fr";
        QJsonObject obj;
        obj["URL"] = CURRENT_URL;
        file.open(QIODevice::WriteOnly);
        file.write(QJsonDocument(obj).toJson());
        file.close();
    }
}

void MainWindow::finishedLoadNotification(bool result)
{
    qDebug() << "finishedLoadNotification" << result;

    if( result == false) /* erreur réseau */
    {
        timewait = 10*1000; /* 10 secondes */
        /* On attend 10 secondes */
        //delay(10);
        //RefreshScreen();
    }
    else /* pas d'erreur réseau */
    {
        timewait = 1800000;  /* 30 minutes */
    }

    timer->setInterval(timewait);
}
