#include "menubutton.h"
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QMouseEvent>
MenuButton::MenuButton(QWidget *parent) : QWidget(parent)
{

}

MenuButton::MenuButton(QString img,QString name,QWidget *parent) : QWidget(parent)
{
    qDebug()<< "添加自定义控件MenuButton";
//    设置鼠标样式为手型
    setCursor(Qt::PointingHandCursor);
//    实例化头文件中定义的三个个私有指针
    menuButtonWidget = new QWidget(this);
    imgLabel = new QLabel();
    nameLabel = new QLabel();


//    创建QPixmap对象
    QPixmap pix;
//    加载图片
    pix.load(img);
//    设置pixmap缩放的尺寸
    pix.scaled(imgLabel->size(), Qt::KeepAspectRatio);
//    设置label的属性scaledContents，这个属性的作用是允许（禁止）label缩放它的内容充满整个可用的空间。
//    特别说明的一点是当使能该属性并且label显示pixmap时，它能够缩放pixmap充满整个可用的空间。
    imgLabel->setScaledContents(true);

    imgLabel->setPixmap(pix);
    nameLabel->setText(name);
    qDebug()<< "imgLabel尺寸["<<imgLabel->width()<<","<<imgLabel->height()<<"]";
    qDebug()<< "nameLabel尺寸["<<nameLabel->width()<<","<<nameLabel->height()<<"]";

//    设置QLabel的对齐方式，对齐方式分为水平和垂直的左右居中三种方式
//    nameLabel->setAlignment(Qt::AlignCenter);
//    imgLabel->setAlignment(Qt::AlignCenter);

//    定义垂直布局 并且设置为当前定义的布局
    QVBoxLayout *vlayout = new QVBoxLayout(menuButtonWidget);
    vlayout->setContentsMargins(0, 0, 0, 0);
//    向布局中添加组件
    vlayout->addWidget(imgLabel);
    vlayout->addWidget(nameLabel);
    vlayout->setAlignment(Qt::AlignHCenter);

//    设置当前widget布局为垂直布局
//    this->setLayout(vlayout);

    resize(parent->width(),this->height());

    qDebug()<< "自定义控件尺寸["<<menuButtonWidget->width()<<","<<menuButtonWidget->height()<<"],父窗体尺寸["<<parent->width()<<","<<parent->height()<<"]";
}

void MenuButton::mousePressEvent(QMouseEvent *event)
{
    qDebug()<< "MenuButton被按下";
    // 如果是鼠标左键按下
    if(event->button()==Qt::LeftButton){
        update();
        emit clicked();
    }

}

void MenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<< "MenuButton按下被松开";
    // 如果是鼠标左键松开
    if(event->button()==Qt::LeftButton){
        update();
    }
}
