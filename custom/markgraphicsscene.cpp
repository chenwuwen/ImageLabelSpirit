﻿#include "markgraphicsscene.h"



MarkGraphicsScene::MarkGraphicsScene(QObject *parent):QGraphicsScene(parent)
{

}


void MarkGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mousePressEvent()方法执行";
//    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {
        if(event->pos() == event->scenePos()){
            qDebug() << "两只一致" << event->pos() ;
        }else{
             qDebug() << "两只bu一致" << event->pos() << event->scenePos();
        }
//        检测光标下是否有 item,如果存在则赋值给oldQGraphicsRectItem
        foreach (QGraphicsItem *item, items(event->scenePos())) {
            if (item->type() == QGraphicsRectItem::Type){
                oldQGraphicsRectItem = dynamic_cast<QGraphicsRectItem *>(item);
                qDebug() << "当前区域存在标注: " << oldQGraphicsRectItem->rect() ;
//                这里直接跳出循环了,如果有两个标注有一部分是重合的,那么只会移动一个
                break;
            }
        }



        if (event->button() == Qt::LeftButton) {

            QPointF point = event->scenePos();
            startPoint = point;
            qDebug() << "startPoint:" << startPoint;

//            按下的是鼠标左键存在两种情况：1.当前存在item -> 此时应为移动 2不存在item -> 此时应为新增
            if(oldQGraphicsRectItem != NULL){
//                此时鼠标应当变为可移动形状
                views().at(0)->setCursor(Qt::SizeAllCursor);
                isMoving = true;
//                有了移动item的趋势,先保存就得item的位置信息,因为一旦item移动,oldQGraphicsRectItem里面的信息就变化了
                oldRectF = oldQGraphicsRectItem->rect();

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
    //             设置为选中状态
                   oldQGraphicsRectItem->setSelected(true);
                   oldQGraphicsRectItem->setBrush(QBrush(QColor(255,215,0),Qt::Dense7Pattern));
                   qDebug() << "item未选中,设置为选中状态,已选中item数量为：" << selectedItems().size();
    //               发射item被选中信号
                   emit itemSelectState(oldQGraphicsRectItem->rect(),true);
                }else{
    //              取消选中状态
                    oldQGraphicsRectItem->setSelected(false);
                    oldQGraphicsRectItem->setBrush(Qt::NoBrush);
                    qDebug() << "item已选中,取消其选中状态,已选中item数量为：" << selectedItems().size();
    //                发射item取消选中信号
                   emit itemSelectState(oldQGraphicsRectItem->rect(),false);
               }
            }
        }

    }
}

void MarkGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    endPoint = point;

//    说明标注结束
    if(event->button()==Qt::LeftButton && isDrawing && rectItem->rect().width() > 0) {
//        如果鼠标左键按着的同时移动鼠标

//        取到的是所有的Item,可以通过item的type属性区分,哪些是QGraphicsRectItem,和其他Item
//        qDebug() << "当前场景Item的数量为：" << items().size();
        QRectF rectf = rectItem->rect();
//        emit addMarkItem(rectf);
        qDebug() << "MarkGraphicsScene 标注结束,startPoint" << startPoint <<  "endPoint:" << endPoint << "标注的尺寸信息是：" << rectf << "item的pos()值：" << rectItem->pos()<< "item的scenePos()返回：" << rectItem->scenePos();
     }

//    说明移动结束
    if(event->button() == Qt::LeftButton && isMoving && endPoint != startPoint) {
//        如果鼠标左键按着的同时移动鼠标

//        这里需要注意的是,如果是移动的情况,那么改变的只是坐标信息,长宽是不进行改变的.只需要操作oldQGraphicsRectItem即可
//        那么已经移动了,如何知道移动后的item坐标呢？ 其实可以通过 endPoint 和 startPoint 算出来


//         新的item信息
        QRectF newRectF = oldQGraphicsRectItem->rect();
        oldQGraphicsRectItem->setRect(newRectF);

//        emit updateMarkItem(oldRectF,newRectF);
        qDebug() << "MarkGraphicsScene 移动Item结束,startPoint" << startPoint <<  "endPoint:" << endPoint << "其原信息：" << oldRectF << " 新的信息：" << oldQGraphicsRectItem->rect() << "oldQGraphicsRectItem的pos()返回：" << oldQGraphicsRectItem->pos() << "oldQGraphicsRectItem的scenePos()返回：" << oldQGraphicsRectItem->scenePos();
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
    QGraphicsScene::mouseMoveEvent(event);

    if(event->buttons() & Qt::LeftButton) {
//        返回鼠标在场景中的位置
        QPointF point = event->scenePos();

        endPoint = point;
        if ( isDrawing ){
//           只有鼠标移动一定的距离才判断是要进行标注,然后开始画标注,因为鼠标一直在移动,所以画标注的步骤是先删之前画的范围,再画新范围.这里需要注意的是：只能从左上角往右下角画
            if(qAbs(endPoint.x()- startPoint.x())>OPERATION_THRESHOLD_VALUE && qAbs(endPoint.y()- startPoint.y())>OPERATION_THRESHOLD_VALUE){
//                画新item之前先移除之前画的
                removeItem(rectItem);
                rectItem->setRect(startPoint.x(), startPoint.y(), qAbs(endPoint.x()-startPoint.x()), qAbs(endPoint.y()-startPoint.y()));
//                配置如何画Item,包括画笔颜色等
                drawRectMark(rectItem);
                addItem(rectItem);
             }
       }

        if ( isMoving ){
//            qAbs()函数求绝对值,移动图元可能往右下角移动也有可能往左上角移动,有可能只水平移动,也有可能只垂直移动
            if(qAbs(endPoint.x()- startPoint.x())>OPERATION_THRESHOLD_VALUE || qAbs(endPoint.y()- startPoint.y())>OPERATION_THRESHOLD_VALUE){
                qDebug() << "移动操作: 场景坐标" << endPoint << "item:" << event->pos();
//                startPoint位置的x轴距离左上角距离
                qreal x_range_top_left_corner = oldQGraphicsRectItem->x() - startPoint.x();
//                startPoint位置的y轴距离左上角距离
                qreal y_range_top_left_corner = oldQGraphicsRectItem->y() - startPoint.y();
//                https://blog.csdn.net/EddyXie/article/details/91489519

//                移动
//                oldQGraphicsRectItem->moveBy(oldRectF.x() + (endPoint.x() - startPoint.x()),oldRectF.y() + (endPoint.y() - startPoint.y()));

//               QPointF f =   oldQGraphicsRectItem->mapToScene(endPoint);
//                oldQGraphicsRectItem->setPos(endPoint.x(),endPoint.y());
                oldQGraphicsRectItem->moveBy(startPoint.x()-endPoint.x(),startPoint.y()-endPoint.y());
//                QGraphicsScene::
//                oldQGraphicsRectItem->setRect(476,334,oldRectF.width(),oldRectF.height());

//                oldQGraphicsRectItem->moveBy(endPoint.x() - x_range_top_left_corner,endPoint.y() - y_range_top_left_corner );
//                oldQGraphicsRectItem->setRect(endPoint.x() - x_range_top_left_corner,endPoint.y() - y_range_top_left_corner,oldRectF.width(),oldRectF.height());
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
