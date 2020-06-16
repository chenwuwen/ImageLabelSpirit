#pragma execution_character_set("utf-8")
#ifndef MARKGRAPHICSPIXMAPITEM_H
#define MARKGRAPHICSPIXMAPITEM_H

#include <QGraphicsRectItem>
#include <QPixmap>
#include <QDebug>
#include <QStyle>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QKeyEvent>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

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

//    设置空格键按下状态,MainInterface.cpp调用
    void setSpaceActive(bool state);

public slots:



protected:
     void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
     void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

//    键盘按下事件
    void keyPressEvent(QKeyEvent *event) override;
//    键盘松开事件
    void keyReleaseEvent(QKeyEvent *event) override;
//    鼠标悬停事件(想要该事件生效需要设置setAcceptHoverEvents(true))
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;


private:
    QPixmap currentPixmap;
//    空格键是否处于按下状态
    bool spaceActive = false;
    QPointF startPixmapItemPoint , startScenePoint , endScenePoint ;
};

#endif // MARKGRAPHICSPIXMAPITEM_H
