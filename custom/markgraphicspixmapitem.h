#ifndef MARKGRAPHICSPIXMAPITEM_H
#define MARKGRAPHICSPIXMAPITEM_H

#include <QGraphicsRectItem>
#include <QPixmap>



class MarkGraphicsPixmapItem:public QGraphicsPixmapItem
{
public:
    MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent = nullptr);
};

#endif // MARKGRAPHICSPIXMAPITEM_H
