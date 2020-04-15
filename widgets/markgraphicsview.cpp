#include "markgraphicsview.h"




MarkGraphicsView::MarkGraphicsView(QWidget *parent):QGraphicsView(parent)
{
      defaultDisplay();
}


void MarkGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug() << "MarkGraphicsView类 mousePressEvent方法执行";
}

void MarkGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "MarkGraphicsView类 mouseMoveEvent方法执行";
//    如果重构了事件函数,并且需要事件传递,需要添加次方法。
    QGraphicsView::mouseMoveEvent(event);
     qDebug() << "开始平移===";
//    当空格键按下时,鼠标移动才生效
    if (!spaceActive) return;
//    左键按下移动才生效
//    if (event->button()!=Qt::LeftButton) return;
    qDebug() << "开始平移";
//    获取每次鼠标在场景坐标系下的平移量
      QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(this->lastMousePos);
//    如果是在缩放之后，调用的平移方法，那么平移量先要乘上缩放比，transform是view的变换矩阵，m11可以用为缩放比
      mouseDelta *= this->transform().m11();
//    调用平移方法
      this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
      this->centerOn(this->mapToScene(QPoint(this->viewport()->rect().width()/ 2 - mouseDelta.x(),
                                                                             this->viewport()->rect().height()/ 2 - mouseDelta.y())));
      this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

      lastMousePos = event->pos();

}

void MarkGraphicsView::wheelEvent(QWheelEvent *event)
{
    qDebug() << "MarkGraphicsView类 wheelEvent方法执行,ctrl键状态："<< ctrlActive;
//       Ctrl键按下,才可以通过鼠标滚轮放大缩小
       if(!ctrlActive) return;

//        获取当前鼠标相对于view的位置;
       QPointF cursorPoint = event->pos();
//       获取当前鼠标相对于scene的位置;
       QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

//       获取view的宽高;
       qreal viewWidth = this->viewport()->width();
       qreal viewHeight = this->viewport()->height();

//       获取当前鼠标位置相当于view大小的横纵比例;
       qreal hScale = cursorPoint.x() / viewWidth;
       qreal vScale = cursorPoint.y() / viewHeight;

//     当前放缩倍数
       qreal scaleFactor = this->matrix().m11();
       int wheelDeltaValue = event->delta();
       if (wheelDeltaValue > 0){
//            向前滚动，放大;
           this->scale(DEFAULT_PROPORTION, DEFAULT_PROPORTION);
       } else{
//            向后滚动，缩小;
           this->scale(1.0 / DEFAULT_PROPORTION, 1.0 / DEFAULT_PROPORTION);

       }

//        将scene坐标转换为放大缩小后的坐标;
          QPointF viewPoint = this->matrix().map(scenePos);
//          通过滚动条控制view放大缩小后的展示scene的位置;
          horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
          verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));

//        发射缩放比例改变的信号
         emit scaleChange();
         QGraphicsView::wheelEvent(event);
}

void MarkGraphicsView::keyPressEvent(QKeyEvent *event)
{
    int key_code = event->key();
//    如果是ctrl键
    if(key_code == Qt::Key_Control){
        ctrlActive = true;
        qDebug()<<"Ctrl被按下,当前ctrlActive："<< ctrlActive;
    }

//    如果是空格键
    if(key_code == Qt::Key_Space){
        spaceActive = true;
        qDebug()<<"Space被按下,当前spaceActive："<< spaceActive;
    }

    QGraphicsView::keyPressEvent(event);
}

void MarkGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    int key_code = event->key();
//    如果是ctrl键
    if(key_code == Qt::Key_Control){
        ctrlActive = false;
        qDebug()<<"Ctrl被释放,当前ctrlActive："<< ctrlActive;
    }

//    如果是空格键
    if(key_code == Qt::Key_Space){
        spaceActive = false;
//        qDebug()<<"Space被释放,当前spaceActive："<< spaceActive;
    }

    QGraphicsView::keyReleaseEvent(event);

}

void MarkGraphicsView::enterEvent(QEvent *event)
{
//    在QGraphicsView子类中使用viewport()->setCursor()，才可以真正的改变鼠标的形状。同时，update()也是如此，需要调用viewport()->update()。
//    viewport()->setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsView::enterEvent(event);
}


void MarkGraphicsView::leaveEvent(QEvent *event)
{
//    在QGraphicsView子类中使用viewport()->setCursor()，才可以真正的改变鼠标的形状。同时，update()也是如此，需要调用viewport()->update()。
//    viewport()->setCursor(QCursor(Qt::ArrowCursor));
    QGraphicsView::leaveEvent(event);
}


void MarkGraphicsView::enlarge()
{
    scale(DEFAULT_PROPORTION,DEFAULT_PROPORTION);
}

void MarkGraphicsView::narrow()
{
    scale(1.0 / DEFAULT_PROPORTION, 1.0 / DEFAULT_PROPORTION);
}


void MarkGraphicsView::adapt()
{
    QList<QGraphicsItem *> items = this->items();
    for (QGraphicsItem *item:items){
        qDebug() << "重回初始大小";
        fitInView(item,Qt::KeepAspectRatio);
    }

}

void MarkGraphicsView::defaultDisplay()
{
    adapt();
}

MarkGraphicsView::~MarkGraphicsView()
{

}
