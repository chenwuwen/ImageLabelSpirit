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
        if (event->button() == Qt::LeftButton) {
            // 在 Scene 上添加一个自定义 item
            QPointF point = event->scenePos();
            startPoint = point;
            qDebug()<<"startPoint:"<<startPoint;
            isDrawing = true;
            rectItem = new QGraphicsRectItem;
        } else if (event->button() == Qt::RightButton) {
            // 检测光标下是否有 item
            QGraphicsItem *itemToRemove = NULL;
            foreach (QGraphicsItem *item, items(event->scenePos())) {
                if (item->type() == QGraphicsRectItem::Type) {
                    itemToRemove = item;
                    break;
                }
            }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
                removeItem(itemToRemove);
        }
    }
}

void MarkGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(event->button()==Qt::LeftButton) {
//        如果鼠标左键按着的同时移动鼠标
        qDebug() << "MarkGraphicsScene mouseReleaseEvent.";
        QPointF point = event->scenePos();
        endPoint = point;
        qDebug()<<"endPoint:"<<endPoint;
//        取到的是所有的Item,可以通过item的type属性区分,哪些是QGraphicsRectItem,和其他Item
        qDebug() << "当前场景Item的数量为：" << items().size();
        emit addMarkItem(rectItem);
     }
}

void MarkGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mouseMoveEvent()方法执行";
    QGraphicsScene::mouseMoveEvent(event);

    if(event->buttons()&Qt::LeftButton) {
        QPointF point = event->scenePos();
        endPoint = point;
        if(endPoint.x()- startPoint.x()>20 && endPoint.y()- startPoint.y()>20){
            removeItem(rectItem);
            QPen p;
            p.setWidth(2);
            p.setColor(QColor(0, 160, 230));
            rectItem->setPen(p);
            rectItem->setRect(startPoint.x(), startPoint.y(), endPoint.x()-startPoint.x(), endPoint.y()-startPoint.y());
            addItem(rectItem);
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
   if (event->key() == Qt::Key_Backspace) {
           // 移除所有选中的 items
           qDebug() << "selected items " << selectedItems().size();
           while (!selectedItems().isEmpty()) {
               removeItem(selectedItems().front());
           }
       } else {
           QGraphicsScene::keyPressEvent(event);
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
