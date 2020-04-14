#include "markgraphicsscene.h"

MarkGraphicsScene::MarkGraphicsScene(QObject *parent):QGraphicsScene(parent)
{

}


void MarkGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mousePressEvent()方法执行";
}

void MarkGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mouseMoveEvent()方法执行";
}

void MarkGraphicsScene::leaveEvent(QGraphicsSceneMouseEvent *event)
{
     qDebug() << "MarkGraphicsScene类的 leaveEvent()方法执行";
}

void MarkGraphicsScene::enterEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 enterEvent()方法执行";
}

void MarkGraphicsScene::keyPressEvent(QKeyEvent *event)
{
   qDebug() << "MarkGraphicsScene类的 keyPressEvent()方法执行";
}

void MarkGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
   qDebug() << "MarkGraphicsScene类的 keyReleaseEvent()方法执行";
}
