#include "markgraphicspixmapitem.h"

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(pixmap);
}

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    QPixmap pixmap;
    pixmap.load(imgPath);
    setPixmap(pixmap);
}
