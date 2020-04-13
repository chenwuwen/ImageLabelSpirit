#ifndef MARKGRAPHICSVIEW_H
#define MARKGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QScrollBar>



class MarkGraphicsView:public QGraphicsView
{
public:
    explicit MarkGraphicsView(QWidget *parent = nullptr);
    ~MarkGraphicsView();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    鼠标滚轮事件
    void wheelEvent(QWheelEvent *event);
//    键盘按下事件
    void keyPressEvent(QKeyEvent *event) ;
//    键盘松开事件
    void keyReleaseEvent(QKeyEvent *event) ;

private:

//    ctrl键是否是按下状态
    bool ctrlActive = false;
//     空格键是否是按下状态
    bool spaceActive = false;

};

#endif // MARKGRAPHICSVIEW_H
