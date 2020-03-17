#include "menubutton.h"
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QDebug>
MenuButton::MenuButton(QWidget *parent) : QWidget(parent)
{

}

MenuButton::MenuButton(QString img,QString name,QWidget *parent) : QWidget(parent)
{
    qDebug()<< "添加自定义控件MenuButton";

//    实例化头文件中定义的三个个私有指针
    menuButtonWidget = new QWidget(this);
    imgLabel = new QLabel(menuButtonWidget);
    nameLabel = new QLabel(menuButtonWidget);


//    imgLabel->setSizePolicy()
//    imgLabel->resize(32,32);
//    menuButtonWidget->resize(80,80);


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

//    设置QLabel的对齐方式，对齐方式分为水平和垂直的左右居中三种方式
    nameLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setAlignment(Qt::AlignCenter);

//    定义垂直布局
    QVBoxLayout *vlayout = new QVBoxLayout(menuButtonWidget);
//    向布局中添加组件
    vlayout->addWidget(imgLabel);
    vlayout->addWidget(nameLabel);

    menuButtonWidget->show();

//    设置当前widget布局为垂直布局
//    this->setLayout(vlayout);

}
