#include "mainwidget.h"
#include "splashwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWidget w;
//    w.show();
//    先启动启动页,再由启动页启动主界面
    SplashWidget splash;
    splash.show();
    return a.exec();
}
