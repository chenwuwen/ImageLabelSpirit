#include "markgraphicsscene.h"

#include <QDrag>



MarkGraphicsScene::MarkGraphicsScene(QObject *parent):QGraphicsScene(parent)
{

}


void MarkGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mousePressEvent()方法执行";
//    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {


//        检测光标下是否有 item,如果存在则赋值给oldQGraphicsRectItem
        foreach (QGraphicsItem *item, items(event->scenePos())) {
            if (item->type() == QGraphicsRectItem::Type){
                oldQGraphicsRectItem = dynamic_cast<QGraphicsRectItem *>(item);
                qDebug() << "当前区域有标注" ;
                break;
            }
        }


        if (event->button() == Qt::LeftButton) {
//            按下的是鼠标左键存在两种情况：1.当前存在item -> 此时应为移动 2不存在item -> 此时应为新增
            if(oldQGraphicsRectItem != NULL){
//                此时鼠标应当变为可移动形状
                views().at(0)->setCursor(Qt::SizeAllCursor);
                isMoving = true;

            }else{
//                这里将isDrawing设置为true,表示将要开始画标注,但其实有两种情况,一种是点击一下,直接弹起来,一种是点击之后不松开开始移动一段距离再松开
//                因此需要在鼠标弹起来时,将其设置为false.
                isDrawing = true;
//              在 Scene 上添加一个自定义 item
                QPointF point = event->scenePos();
                startPoint = point;
                qDebug()<<"startPoint:"<<startPoint;
                rectItem = new QGraphicsRectItem;
            }

        } else if (event->button() == Qt::RightButton) {
            if(!oldQGraphicsRectItem->isSelected()){
//                    设置为选中状态
               oldQGraphicsRectItem->setSelected(true);
               qDebug() << "item未选中,设置为选中状态,已选中item数量为：" << selectedItems().size();
            }else{
//              取消选中状态
                oldQGraphicsRectItem->setSelected(false);
                qDebug() << "item已选中,取消其选中状态,已选中item数量为：" << selectedItems().size();
           }
        }
    }
}

void MarkGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

//    说明标注结束
    if(event->button()==Qt::LeftButton && isDrawing && rectItem->rect().width() > 0) {
//        如果鼠标左键按着的同时移动鼠标
        qDebug() << "MarkGraphicsScene mouseReleaseEvent.";
        QPointF point = event->scenePos();
        endPoint = point;
        qDebug()<< "endPoint:" << endPoint;
//        取到的是所有的Item,可以通过item的type属性区分,哪些是QGraphicsRectItem,和其他Item
        qDebug() << "当前场景Item的数量为：" << items().size();
        QRectF rectf = rectItem->rect();
        emit addMarkItem(rectf);
     }

//    说明移动结束
    if(event->button()==Qt::LeftButton && isMoving) {
//        如果鼠标左键按着的同时移动鼠标
        qDebug() << "MarkGraphicsScene mouseReleaseEvent.";
        QPointF point = event->scenePos();
        endPoint = point;
//        这里需要注意的是,如果是移动的情况,那么改变的只是坐标信息,长宽是不进行改变的.只需要操作oldQGraphicsRectItem即可
//        那么已经移动了,如何知道移动后的item坐标呢？ 其实可以通过 endPoint 和 startPoint 算出来

//        x轴方向移动的距离
        qreal xMoving = endPoint.x() - startPoint.x();
//        y轴方向移动的距离
        qreal yMoving = endPoint.y() - startPoint.y();
//        旧的item信息
        QRectF oldRectF = oldQGraphicsRectItem->rect();
//         新的item信息
        QRectF newRectF = QRectF(oldRectF.x() + xMoving,oldRectF.y() + yMoving,oldRectF.width(),oldRectF.height());

        oldQGraphicsRectItem->setRect(newRectF);
        emit updateMarkItem(oldRectF,newRectF);

     }

    isMoving = false;
    isDrawing = false;
    views().at(0)->setCursor(Qt::ArrowCursor);
}

void MarkGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mouseMoveEvent()方法执行";
    QGraphicsScene::mouseMoveEvent(event);

    if(event->buttons()&Qt::LeftButton) {
        QPointF point = event->scenePos();
        endPoint = point;
        if (isDrawing){
//        只有鼠标移动一定的距离才判断是要进行标注,然后开始画标注,因为鼠标一直在移动,所以画标注的步骤是先删之前画的范围,再画新范围
        if(endPoint.x()- startPoint.x()>20 && endPoint.y()- startPoint.y()>20){

            removeItem(rectItem);
            rectItem->setRect(startPoint.x(), startPoint.y(), endPoint.x()-startPoint.x(), endPoint.y()-startPoint.y());
            drawRectMark(rectItem);
            addItem(rectItem);
        }
       }
    }


}

void MarkGraphicsScene::leaveEvent(QGraphicsSceneMouseEvent *event)
{
     qDebug() << "MarkGraphicsScene类的 leaveEvent()方法执行";
}

void MarkGraphicsScene::enterEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 enterEvent()方法执行";
    if(spaceActive){
//       QGraphicsScene中没有设置鼠标样式的方法,因此需要选获取view
         QGraphicsView *view = this->views().at(0);
//         当空格键是激活状态,鼠标在场景中时应该为手型
         view->setCursor(QCursor(Qt::OpenHandCursor));
    }

}

void MarkGraphicsScene::keyPressEvent(QKeyEvent *event)
{
   qDebug() << "MarkGraphicsScene类的 keyPressEvent()方法执行";
   QGraphicsScene::keyPressEvent(event);
   int key_code = event->key();
//    如果是ctrl键
   if(key_code == Qt::Key_Control){
       ctrlActive = true;
//     qDebug()<<"Ctrl被按下,当前ctrlActive："<<ctrlActive;
   }

//    如果是空格键
   if(key_code == Qt::Key_Space){
       spaceActive = true;
//     qDebug()<<"Space被按下,当前spaceActive："<<spaceActive;
   }

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
   QGraphicsScene::keyReleaseEvent(event);

   int key_code = event->key();
//    如果是ctrl键
   if(key_code == Qt::Key_Control){
       ctrlActive = false;
//     qDebug()<<"Ctrl被释放,当前ctrlActive："<<ctrlActive;
   }

//    如果是空格键
   if(key_code == Qt::Key_Space){
       spaceActive = false;
//     qDebug()<<"Space被释放,当前spaceActive："<<spaceActive;
   }
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
