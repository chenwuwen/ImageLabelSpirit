#pragma execution_character_set("utf-8")
#ifndef MARKGRAPHICSVIEW_H
#define MARKGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScrollBar>
#include <QList>
#include <QDrag>

#include <custom/markgraphicspixmapitem.h>

class MarkGraphicsView:public QGraphicsView
{

      Q_OBJECT

public:
    explicit MarkGraphicsView(QWidget *parent = nullptr);
    ~MarkGraphicsView();



//    放大,固定比例。点击放大按钮执行
   void enlarge();
//    缩小,固定比例。点击缩小按钮执行
   void narrow();
//   适应窗口大小
   void adapt();


signals:
//   自定义信号,缩放比例改变。信号
   void scaleChange();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    鼠标滚轮事件
    void wheelEvent(QWheelEvent *event);
//    键盘按下事件
    void keyPressEvent(QKeyEvent *event) ;
//    键盘松开事件
    void keyReleaseEvent(QKeyEvent *event) ;
//    鼠标移入事件
    void enterEvent(QEvent *);
//    鼠标移出事件
    void leaveEvent(QEvent *);
//    拖拽首先进入QGraphicsView触发其dragEnterEvent事件
    void dragEnterEvent(QDragEnterEvent *event);

private:

//    ctrl键是否是按下状态
    bool ctrlActive = false;
//     空格键是否是按下状态
    bool spaceActive = false;

//    固定比例 https://www.zhihu.com/question/35614219
    constexpr const static double DEFAULT_PROPORTION = 1.2;



};

#endif // MARKGRAPHICSVIEW_H
