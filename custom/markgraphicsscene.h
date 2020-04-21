#pragma execution_character_set("utf-8")
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

//    从之前持久化的数据中画标注
    void addItemFromStorage(QRectF);

//    画标注[矩形标注]
    void drawRectMark(QGraphicsRectItem *rectItem);

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
    void addMarkItem(QRectF);
//     删除了一个Item的信号
    void deleteMarkItem(QRectF);
//    更改了一个Item信息(主要是移动item的位置)
    void updateMarkItem(QRectF oldRectF,QRectF newRectF);

//    Item被选中,或者取消选中 信号
    void itemSelectState(QRectF,bool);

private:
    bool ctrlActive = false;
    bool spaceActive = false;
    bool isDrawing = false;
    bool isMoving = false;
//    开始点位置,结束点位置
    QPointF startPoint,endPoint;
//    矩形框item
    QGraphicsRectItem *rectItem;

//    旧的标注
    QGraphicsRectItem *oldQGraphicsRectItem = NULL;
//    旧标注的信息
    QRectF oldRectF;


};

#endif // MARKGRAPHICSSCENE_H
