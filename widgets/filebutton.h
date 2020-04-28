#pragma execution_character_set("utf-8")
#ifndef FILEBUTTON_H
#define FILEBUTTON_H

#include <QPaintEvent>
#include <QStyleOption>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QGraphicsDropShadowEffect>

class FileButton : public QWidget
{
    Q_OBJECT
public:
    explicit FileButton(QWidget *parent = nullptr);


//    表示鼠标按下的事件
    void mousePressEvent(QMouseEvent *event);

//    表示鼠标释放的事件
    void mouseReleaseEvent(QMouseEvent *event);

//    表示鼠标移动事件(鼠标在控件内按住移动会触发该方法,如果不需要按住移动,需要在控件构造方法中添加 setMouseTracking(true);这样鼠标不按住移动也会触发该方法)
    void mouseMoveEvent(QMouseEvent *event);

protected:
    //重写绘图事件
    //如果在窗口绘图，必须在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);

//    鼠标移入事件
    void enterEvent(QEvent *);
//    鼠标移出事件
    void leaveEvent(QEvent *);


signals:
//    点击信号
    void clicked();

public slots:

   void draw_path(QString path);

private:
   int lineWidth=2;
    QString pathInfo;
    QColor defaultLineColor=Qt::gray;
    QColor lineColor = defaultLineColor;
};

#endif // FILEBUTTON_H
