#include "markgraphicsscene.h"

#define cout qDebug() << "[" <<__FILE__<< " : "<<__LINE__<<"]"

MarkGraphicsScene::MarkGraphicsScene(QObject *parent):QGraphicsScene(parent)
{

}


void MarkGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mousePressEvent()方法执行";

    if (!event->isAccepted()) {

//        event->pos() / event->scenePos() 结果是不一致的,event->pos() 的结果是(0,0)

//        检测光标下是否有 item,如果存在则赋值给oldQGraphicsRectItem
        foreach (QGraphicsItem *item, items(event->scenePos())) {
            if (item->type() == QGraphicsRectItem::Type){
                oldQGraphicsRectItem = dynamic_cast<QGraphicsRectItem *>(item);
                cout << "当前区域存在标注: " << oldQGraphicsRectItem->rect() ;
//                这里直接跳出循环了,如果有两个标注有一部分是重合的,那么只会移动一个
                break;
            }
        }


        if (event->button() == Qt::LeftButton) {
            QPointF point = event->scenePos();
            startScenePoint = point;
            cout << "startScenePoint:" << startScenePoint;

//            按下的是鼠标左键存在两种情况：1.当前存在item -> 此时应为移动 2不存在item -> 此时应为新增
            if(oldQGraphicsRectItem != NULL){
//                此时鼠标应当变为可移动形状
                views().at(0)->setCursor(Qt::SizeAllCursor);
                isMoving = true;
//                有了移动item的趋势,先保存就得item的位置信息,因为一旦item移动,oldQGraphicsRectItem里面的信息就变化了
                oldRectF = oldQGraphicsRectItem->rect();
                startRectItemPoint = oldQGraphicsRectItem->pos();

            }else{
//                这里将isDrawing设置为true,表示将要开始画标注,但其实有两种情况,一种是点击一下,直接弹起来,一种是点击之后不松开开始移动一段距离再松开
//                因此需要在鼠标弹起来时,将其设置为false.
                isDrawing = true;
//              实例化QGraphicsRectItem 准备在scene场景上添加,之所以说是准备添加,是因为只有触发mouseMoveEvent()方法才能添加item,现在只是实例化出来
                rectItem = new QGraphicsRectItem;
            }

        }

        if (event->button() == Qt::RightButton) {
            if(oldQGraphicsRectItem != NULL){
                if(!oldQGraphicsRectItem->isSelected()){
//                 设置为选中状态
                   oldQGraphicsRectItem->setSelected(true);
                   oldQGraphicsRectItem->setBrush(QBrush(QColor(255,215,0),Qt::Dense7Pattern));
                   cout << "item未选中,设置为选中状态,已选中item数量为：" << selectedItems().size();
//                   发射item被选中信号
                   emit itemSelectState(oldQGraphicsRectItem->rect(),true);
                }else{
//                  取消选中状态
                    oldQGraphicsRectItem->setSelected(false);
                    oldQGraphicsRectItem->setBrush(Qt::NoBrush);
                    qDebug() << "item已选中,取消其选中状态,已选中item数量为：" << selectedItems().size();
//                    发射item取消选中信号
                   emit itemSelectState(oldQGraphicsRectItem->rect(),false);
               }
            }
        }

       QGraphicsScene::mousePressEvent(event);
    }

}

void MarkGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    endScenePoint = point;

//    说明标注结束
    if(event->button()==Qt::LeftButton && isDrawing && rectItem->rect().width() > 0) {
//        如果鼠标左键按着的同时移动鼠标

//        取到的是所有的Item,可以通过item的type属性区分,哪些是QGraphicsRectItem,和其他Item
//        qDebug() << "当前场景Item的数量为：" << items().size();
        QRectF rectf = rectItem->rect();
        emit addMarkItem(rectf);
        cout << "MarkGraphicsScene 标注结束,startScenePoint" << startScenePoint <<  "endScenePoint:" << endScenePoint << "标注的尺寸信息是：" << rectf << "item的pos()值：" << rectItem->pos()<< "item的scenePos()返回：" << rectItem->scenePos();
     }

//    说明移动结束
    if(event->button() == Qt::LeftButton && isMoving && endScenePoint != startScenePoint) {
//        如果鼠标左键按着的同时移动鼠标

//        这里需要注意的是,如果是移动的情况,那么改变的只是坐标信息,长宽是不进行改变的.只需要操作oldQGraphicsRectItem即可
//        那么已经移动了,如何知道移动后的item坐标呢？ 其实可以通过 endScenePoint 和 startScenePoint 算出来

        qreal xMove =  startScenePoint.x() - endScenePoint.x();
        qreal yMove =  startScenePoint.y() - endScenePoint.y();
//         新的item信息
        QRectF newRectF = oldQGraphicsRectItem->rect();
//        oldQGraphicsRectItem->setRect(newRectF);

//        emit updateMarkItem(oldRectF,newRectF);
        qDebug() << "MarkGraphicsScene 移动Item结束,startScenePoint" << startScenePoint <<  "endScenePoint:" << endScenePoint << "其原信息：" << oldRectF << " 新的信息：" << oldQGraphicsRectItem->rect() << "oldQGraphicsRectItem的pos()返回：" << oldQGraphicsRectItem->pos() << "oldQGraphicsRectItem的scenePos()返回：" << oldQGraphicsRectItem->scenePos();
     }

    isMoving = false;
    isDrawing = false;
    oldQGraphicsRectItem = NULL;
    views().at(0)->setCursor(Qt::ArrowCursor);
    QGraphicsScene::mouseReleaseEvent(event);
}

void MarkGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "MarkGraphicsScene类的 mouseMoveEvent()方法执行";

    if (spaceActive) {
//        如果此时空格键是按下状态,则事件直接传递到图元,不再在场景中做任何操作
        QGraphicsScene::mouseMoveEvent(event);
        return ;
    }
    if(event->buttons() & Qt::LeftButton) {
//        返回鼠标在场景中的位置
        QPointF point = event->scenePos();

        endScenePoint = point;
//        鼠标移动X/Y轴距离,其值可正可负
        qreal xMoveLength = endScenePoint.x() - startScenePoint.x();
        qreal yMoveLength = endScenePoint.y() - startScenePoint.y();
        if ( isDrawing ){
//           只有鼠标移动一定的距离才判断是要进行标注,然后开始画标注,因为鼠标一直在移动,所以画标注的步骤是先删之前画的范围,再画新范围.这里需要注意的是：只能从左上角往右下角画

            if(qAbs(xMoveLength) > OPERATION_THRESHOLD_VALUE && qAbs(yMoveLength) > OPERATION_THRESHOLD_VALUE){
//              画新item之前先移除之前画的
                removeItem(rectItem);

//                以标注的图形的左上角为起点,右下角的终点。
                if (xMoveLength < 0 && yMoveLength < 0){
//                    如果移动的距离X/Y轴都为负值,相当于startScenePoint为终点,起点在移动 则item的起点为endScenePoint
                    rectItem->setRect(endScenePoint.x(), endScenePoint.y(), qAbs(startScenePoint.x() - endScenePoint.x()), qAbs(startScenePoint.y() - endScenePoint.y()));
                }else if (xMoveLength < 0 && yMoveLength > 0){
//                    如果移动的距离X为负值,Y为正值,则设置终点为下
                    rectItem->setRect(endScenePoint.x(), startScenePoint.y(), qAbs(startScenePoint.x() - endScenePoint.x()), qAbs(yMoveLength));
                }else if (xMoveLength > 0 && yMoveLength < 0){
//                    如果移动的距离Y为负值,X为正值,则设置终点为下
                    rectItem->setRect(startScenePoint.x(), endScenePoint.y(), qAbs(xMoveLength), qAbs(startScenePoint.y() - endScenePoint.y()));
                }else{
//                    如果移动的距离X/Y轴都为正值,则startScenePoint为起点,最正常/好理解的一种方式
                    rectItem->setRect(startScenePoint.x(), startScenePoint.y(), qAbs(xMoveLength), qAbs(yMoveLength));
                }
//              配置如何画Item,包括画笔颜色等
                drawRectMark(rectItem);
                addItem(rectItem);
             }
       }

        if ( isMoving ){
//            qAbs()函数求绝对值,移动图元可能往右下角移动也有可能往左上角移动,有可能只水平移动,也有可能只垂直移动
            if(qAbs(xMoveLength) > OPERATION_THRESHOLD_VALUE || qAbs(yMoveLength) > OPERATION_THRESHOLD_VALUE){
                cout << "移动标注图元操作: 场景坐标" << endScenePoint << "item:" << event->pos();
//                计算偏移
                qreal xInterval = endScenePoint.x() - startScenePoint.x();
                qreal yInterval = endScenePoint.y() - startScenePoint.y();
//                移动标注框,除了可以使用setPos移动还可以使用moveBy
//                https://blog.csdn.net/EddyXie/article/details/91489519
//                https://blog.csdn.net/douzhq/article/details/105017924
                QPointF moveToPoint = startRectItemPoint + QPointF(xInterval,yInterval);
                oldQGraphicsRectItem->setPos(moveToPoint);
//                oldQGraphicsRectItem->setRect(moveToPoint.x(),moveToPoint.y(),oldQGraphicsRectItem->rect().width(),oldQGraphicsRectItem->rect().height());
            }
        }

    }


}


void MarkGraphicsScene::keyPressEvent(QKeyEvent *event)
{
   qDebug() << "MarkGraphicsScene类的 keyPressEvent()方法执行";
   QGraphicsScene::keyPressEvent(event);

   if (event->key() == Qt::Key_Space) spaceActive = true;

//   如果是删除键
   if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
           // 移除所有选中的 items
           qDebug() << "selected items " << selectedItems().size();
           while (!selectedItems().isEmpty()) {
//               front()方法,取出QList中的第一个元素
               QGraphicsItem *item = selectedItems().front();
               emit deleteMarkItem(dynamic_cast<QGraphicsRectItem *>(item)->rect());
               removeItem(item);

            }
    }
}

void MarkGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
   qDebug() << "MarkGraphicsScene类的 keyReleaseEvent()方法执行";
   if (event->key() == Qt::Key_Space) spaceActive = false;
   QGraphicsScene::keyReleaseEvent(event);
}

void MarkGraphicsScene::saveMarkItem()
{
     QList<QPointF> list;
     QList<QGraphicsItem *> itemList = this->items();
     for (QGraphicsItem *it:itemList){
//        通过item的type来判断item的类型
        int typeCode =  it->type();
        if(typeCode == QGraphicsRectItem::Type){
          QPointF pf = it->pos();
          list << pf;
        }
     }
}

void MarkGraphicsScene::addItemFromStorage(QRectF rectF)
{
    QGraphicsRectItem *rectItem = new QGraphicsRectItem;
    rectItem->setRect(rectF);
    drawRectMark(rectItem);
    addItem(rectItem);
}

void MarkGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
     qDebug() << "MarkGraphicsScene类的 dragEnterEvent()方法执行";
     event->accept();
}

void MarkGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
     qDebug() << "MarkGraphicsScene类的 dragMoveEvent()方法执行";
     event->accept();
}

void MarkGraphicsScene::drawRectMark(QGraphicsRectItem *rectItem)
{
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(0, 160, 230));
    rectItem->setPen(p);
//    设置item 可选择/可移动 (不设置此flag item将无法移动和选中,当为选中状态时,会出现蚂蚁线)
    rectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

}

void MarkGraphicsScene::setSpaceActive(bool state)
{
    spaceActive = state;
}
