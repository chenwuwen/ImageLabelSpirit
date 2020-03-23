#ifndef MEUNBUTTON_H
#define MEUNBUTTON_H

#include <QWidget>
#include <QString>
#include <QtWidgets/QLabel>

class MenuButton : public QWidget
{
    Q_OBJECT
public:


    explicit MenuButton(QWidget *parent = nullptr);

    explicit MenuButton(QString img ,QString name,QWidget *parent = nullptr );

    //表示一个矩形

    QRect _rect;

//    用来表示是否按下了的布尔值
    bool _pressed;

//    表示鼠标按下的事件
    void mousePressEvent(QMouseEvent *);

//    表示鼠标释放的事件
    void mouseReleaseEvent(QMouseEvent *);


signals:
//    信号，点击的信号,这里为什么定义了一个clicked()的信号？因为我们继承的是QWidget,其本身并没有clicked信号,所以
//    在上面我们定义了鼠标按下和松开的方法,当鼠标按下时即 发射 clicked信号
    void clicked();

public slots:

private:
    QLabel *nameLabel;
    QLabel *imgLabel;
    QWidget *menuButtonWidget;
};


#endif // MEUNBUTTON_H
