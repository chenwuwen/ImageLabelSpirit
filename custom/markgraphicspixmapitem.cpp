#include "markgraphicspixmapitem.h"

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    QPixmap pixmap;
    pixmap.load(imgPath);
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

void MarkGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 mouseMoveEvent() 方法执行";
    QGraphicsItem::mouseMoveEvent(event);
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

}

void MarkGraphicsPixmapItem::keyReleaseEvent(QKeyEvent *event)
{

}
