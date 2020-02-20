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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Arguments */

    const QStringList args = QCoreApplication::arguments();
    // Si le programme a été ouvert par le biais d'un fichier
    if(args.count() > 1)
    {
        CURRENT_URL = args[1];
    }
    else
    {
        CURRENT_URL = "https://admoov.albertdemun.education/";
    }

    /* Web browser */

    view = new QWebView(this);
    setCentralWidget(view);
    QObject::connect(view->page(), SIGNAL(loadFinished(bool)), this, SLOT(finishedLoadNotification(bool)));

    /* FullScreen */

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
