#pragma execution_character_set("utf-8")
#ifndef SPLASHWIDGET_H
#define SPLASHWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QMovie>

#include "maininterface.h"
#include "indexinterface.h"



namespace Ui {
class SplashWidget;
}

//启动页
class SplashWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SplashWidget(QWidget *parent = nullptr);
    ~SplashWidget();

private:
    Ui::SplashWidget *ui;
    QMovie *movie;
    int frameCount;

protected slots:
//    启动到主界面
    void startMainInterface();
    void stopMovieAndStartMainInterface(int);
};

#endif // SPLASHWIDGET_H
