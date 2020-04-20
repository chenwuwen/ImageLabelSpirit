#pragma execution_character_set("utf-8")
#ifndef MARKGRAPHICSPIXMAPITEM_H
#define MARKGRAPHICSPIXMAPITEM_H

#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QStyle>
#include <QCursor>



class MarkGraphicsPixmapItem:public QObject,public QGraphicsPixmapItem
{

    Q_OBJECT

public:
    MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent = nullptr);
//    自定义type值
    enum {Type = 1993};
    int type() const override {return Type;}

//    图片原始尺寸
    QSize getOriginalSize();

protected:
     void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

//    鼠标移入事件
    void enterEvent(QEvent *);
//    鼠标移出事件
    void leaveEvent(QEvent *);

//    键盘按下事件
    void keyPressEvent(QKeyEvent *event) ;
//    键盘松开事件
    void keyReleaseEvent(QKeyEvent *event) ;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);


private:
    QPixmap currentPixmap;
//    空格键是否处于按下状态
    bool spaceActive = false;
};

#endif // MARKGRAPHICSPIXMAPITEM_H
