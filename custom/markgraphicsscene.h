#ifndef MARKGRAPHICSSCENE_H
#define MARKGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QCursor>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>

class MarkGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

    MarkGraphicsScene(QObject *parent = nullptr);

public slots:
//    保存标注的Item信息
    void saveMarkItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void leaveEvent(QGraphicsSceneMouseEvent *event);
    void enterEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent  *event);
    void keyReleaseEvent(QKeyEvent  *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

signals:
//    信号参数不能为抽象类

//    添加了一个Item的信号
    void addMarkItem(QGraphicsRectItem);
//     删除了一个Item的信号
    void deleteMarkItem(QGraphicsItem);

private:
    bool ctrlActive = false;
    bool spaceActive = false;
    bool isDrawing;
//    开始点位置,结束点位置
    QPointF startPoint,endPoint;
//    矩形框item
    QGraphicsRectItem *rectItem;


};

#endif // MARKGRAPHICSSCENE_H
