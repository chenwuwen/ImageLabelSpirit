#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QAbstractButton>
#include <QObject>
#include <QWidget>
#include <QPushButton>

class MenuButton : public QPushButton
{
     Q_OBJECT

public:
   explicit MenuButton(QWidget *parent = nullptr);
   explicit MenuButton(QString img,QString text,bool check_able = false ,QWidget *parent = nullptr);
    ~MenuButton();

protected:
    void paintEvent(QPaintEvent *);

//    当按钮已在选中状态时,再次点击时的操作
//    void nextCheckState();

public slots:


private:
//    按钮背景图片路径
    QString img;
//    按钮名称
    QString text;
//    默认内边距
    int defaultPadding = 4;



};

#endif // MENUBUTTON_H
