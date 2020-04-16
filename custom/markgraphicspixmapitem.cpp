#include "markgraphicspixmapitem.h"

#include <QDrag>

//QGraphicsItem的mouseMoveEvent()函数必须鼠标按下的情况下进行move才会触发。
//QWidget的mouseMoveEvent()函数可以通过设置setMouseTracking(true)在鼠标不需要按下的情况下，触发鼠标move事件。
//QGraphicsItem要实现鼠标不按下的情况下，获取鼠标move事件，可通过QGraphicsItem::setAcceptHoverEvents ()来实现，可通过设置setAcceptHoverEvents(true)使其生效
//打开这个选项，就可以接收到以下事件了hoverEnterEvent(), hoverMoveEvent(), and hoverLeaveEvent().

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    获得拖拽支持
    setAcceptDrops(true);
//    setAcceptHoverEvents(true);
//    可选择
//    setFlags(QGraphicsItem::ItemIsSelectable | );
//    可移动
    setFlags(QGraphicsItem::ItemIsMovable);
}

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    QPixmap pixmap;
    pixmap.load(imgPath);
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    获得拖拽支持
    setAcceptDrops(true);
//    setAcceptHoverEvents(true);
//    可选择
//    setFlags(QGraphicsItem::ItemIsSelectable);
//   可移动
    setFlags(QGraphicsItem::ItemIsMovable);
}

void MarkGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 mouseMoveEvent() 方法执行";
    QGraphicsItem::mouseMoveEvent(event);
//    if(spaceActive) {
//        如果是空格键按下状态鼠标移动则是拖拽事件
//        QDrag *drag = new QDrag(event->widget());
//        drag->start();
//    }else{
//        QGraphicsRectItem *rectItem = new QGraphicsRectItem;
//    }
}


void MarkGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 mousePressEvent() 方法执行";
//    QGraphicsItem::mousePressEvent(event);
}

void MarkGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 mouseReleaseEvent() 方法执行";
    QGraphicsItem::mouseReleaseEvent(event);
}

void MarkGraphicsPixmapItem::enterEvent(QEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 enterEvent() 方法执行";
//    设置鼠标为打开手型
    setCursor(QCursor(Qt::OpenHandCursor));
}

void MarkGraphicsPixmapItem::leaveEvent(QEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 leaveEvent() 方法执行";
//    设置鼠标为正常选择形状
    setCursor(QCursor(Qt::ArrowCursor));
}

void MarkGraphicsPixmapItem::keyPressEvent(QKeyEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 keyPressEvent() 方法执行";
    QGraphicsPixmapItem::keyPressEvent(event);
}

void MarkGraphicsPixmapItem::keyReleaseEvent(QKeyEvent *event)
{
//    qDebug()<< "MarkGraphicsPixmapItem类 的 keyReleaseEvent() 方法执行";
}

void MarkGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<< "MarkGraphicsPixmapItem类 的 hoverEnterEvent() 方法执行";
//    setCursor(QCursor(Qt::OpenHandCursor));
}

void MarkGraphicsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<< "MarkGraphicsPixmapItem类 的 hoverLeaveEvent() 方法执行";
}

void MarkGraphicsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<< "MarkGraphicsPixmapItem类 的 hoverMoveEvent() 方法执行";
}
