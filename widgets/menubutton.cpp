#include "menubutton.h"
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>

MenuButton::MenuButton(QWidget *parent) : QWidget(parent)
{

}

MenuButton::MenuButton(QString img,QString name,QWidget *parent) : QWidget(parent)
{
    QLabel *imgLabel = new QLabel;
    QLabel *nameLabel = new QLabel;
//    创建QPixmap对象
    QPixmap pix;
//    加载图片
    pix.load(img);
    imgLabel->setPixmap(pix);
    nameLabel->setText(name);
//    当照片大小和QLabel大小不适应时，可以设置 这样照片会自动适应大小
    imgLabel->setScaledContents(true);
//    设置QLabel的对齐方式，对齐方式分为水平和垂直的左右居中三种方式
    nameLabel->setAlignment(Qt::AlignCenter);
//    垂直布局
    QVBoxLayout *layout = new QVBoxLayout(parent);
    layout->addWidget(imgLabel);
    layout->addWidget(nameLabel);

}
