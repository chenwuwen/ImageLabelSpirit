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
//    当最后一个可视的窗口退出时候，程序是否退出，默认为true
    a.setQuitOnLastWindowClosed(true);
    return a.exec();
}
