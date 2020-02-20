/*
$Id: main.cpp 33 2020-02-15 09:38:15Z obooklage $
$Revision: 33 $
$Author: obooklage $
$HeadURL: https://svn1.mecavideofrance.com/SVN/DEV/com.obooklage.pi4.admoovqt/src/main.cpp $
$Date: 2020-02-15 10:38:15 +0100 (sam. 15 févr. 2020) $
*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
