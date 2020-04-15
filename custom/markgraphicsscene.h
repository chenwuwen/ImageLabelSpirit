#ifndef MARKGRAPHICSSCENE_H
#define MARKGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QCursor>
#include <QGraphicsView>


class MarkGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    MarkGraphicsScene(QObject *parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void leaveEvent(QGraphicsSceneMouseEvent *event);
    void enterEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent  *event);
    void keyReleaseEvent(QKeyEvent  *event);

private:
    bool ctrlActive = false;
    bool spaceActive = false;

};

#endif // MARKGRAPHICSSCENE_H
