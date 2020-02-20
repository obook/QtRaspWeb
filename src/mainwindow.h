/*
$Id: mainwindow.h 33 2020-02-15 09:38:15Z obooklage $
$Revision: 33 $
$Author: obooklage $
$HeadURL: https://svn1.mecavideofrance.com/SVN/DEV/com.obooklage.pi4.admoovqt/src/mainwindow.h $
$Date: 2020-02-15 10:38:15 +0100 (sam. 15 févr. 2020) $
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwebview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebView *view;
    QString CURRENT_URL;
    QTimer *timer;
    void delay(int sec);
    int timewait;

private slots:
    void RefreshScreen();
    void finishedLoadNotification(bool result);
signals:
    // c'est dans la QWebView qu'il faudrait voir void mousePressEvent(QMouseEvent *);
};

#endif // MAINWINDOW_H
