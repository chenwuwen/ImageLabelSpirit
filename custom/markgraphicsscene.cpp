#include "markgraphicsscene.h"

MarkGraphicsScene::MarkGraphicsScene(QObject *parent):QGraphicsScene(parent)
{

}


void MarkGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mousePressEvent()方法执行";
    QGraphicsScene::mousePressEvent(event);
}

void MarkGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsScene类的 mouseMoveEvent()方法执行";
    QGraphicsScene::mouseMoveEvent(event);
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
