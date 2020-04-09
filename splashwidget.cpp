#include "mainwidget.h"
#include "splashwidget.h"
#include "ui_splashwidget.h"

#include <QTimer>
#include <QDebug>
#include <QMovie>


SplashWidget::SplashWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SplashWidget)
{
    ui->setupUi(this);

//     配置无边框
    QWidget::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

//    QTimer使用方式包括两种
//    1.重复定时,每次时间到,都会执行对应槽函数
//    2.单次执行,需要用到一个静态方法 QTimer::singleShot

//    这是重复执行
//    QTimer *timer = new QTimer(this);
//    connect(timer,&QTimer::timeout,this,&SplashWidget::startMainWidget);
//    timer->start(3000);

//    QTimer的时间单位是毫秒
//      这是单次执行
    QTimer::singleShot(1000,this,&SplashWidget::startMainWidget);


//    QMovie *movie = new QMovie("C:\\Users\\HLWK-06\\Desktop\\splash.gif");
//    movie->setCacheMode(QMovie::CacheAll);
//    ui->label->setMovie(movie);
//    int width = this->width();
//    int height = this->height();
//    填充
//    movie->setScaledSize(QSize(width, height));

//    int height = movie->currentImage().height();
//    int width = movie->currentImage().height();
//    if(movie->currentImage().height() > 0){//根据动画的当前帧高宽比例，调整QLabel和动画的大小
//        width = movie->currentImage().width() / movie->currentImage().height();
//    }
//    this->resize(width, height);
//    movie->setScaledSize(QSize(width, height));

//    movie->start();

//    QMovie是循环播放的,这里也可以设置为值播放一次。通过QMovie的frameCount得到gif帧数，连接frameChanged信号，槽函数判断如果是最后1帧或者第2次播放第1帧时调用stop就行了。
//    frameCount = movie->frameCount();
//    qDebug()<<"当前Movie总帧数："<< frameCount;
//    connect(movie,static_cast<void (QMovie::*)(int)>(&QMovie::frameChanged),this,&SplashWidget::stopMovieAndStartMainWidget);

}

SplashWidget::~SplashWidget()
{
    qDebug()<<"SplashWidget析构函数执行";
    delete ui;
}

void SplashWidget::startMainWidget()
{
    qDebug()<<"跳转到主界面";
//    这里的MainWidget一定要使用new才可以,不能直接定义MainWidget w,如果直接定义,则show()方法不能显示MainWidget
    MainWidget *w = new MainWidget;
    w->show();
    this->close();

}

void SplashWidget::stopMovieAndStartMainWidget(int i)
{
    qDebug()<<"当前Movie帧数："<< i;

//    只播放一次,如果要播放多次,那么就需要引入一个计数器,通过计数器与总帧数的计算得到播放次数
    if(i == 0){
        MainWidget *w = new MainWidget;
        w->show();
        this->close();
        movie->stop();

    }
}
