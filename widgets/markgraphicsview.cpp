#include "markgraphicsview.h"




MarkGraphicsView::MarkGraphicsView(QWidget *parent):QGraphicsView(parent)
{

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
//    当空格键按下时,鼠标移动才生效
    if (!spaceActive) return;
//    左键按下移动才生效
    if (event->button()!=Qt::LeftButton) return;
    QPoint point = event->pos();

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

       // 将scene坐标转换为放大缩小后的坐标;
          QPointF viewPoint = this->matrix().map(scenePos);
          // 通过滚动条控制view放大缩小后的展示scene的位置;
//          horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
//          verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));

//        发射缩放比例改变的信号
        emit scaleChange();
        QGraphicsView::wheelEvent(event);
}

void MarkGraphicsView::keyPressEvent(QKeyEvent *event)
{
    int key_code = event->key();
//    如果是ctrl键
    if(key_code == Qt::Key_Control){
        ctrlActive = !ctrlActive;
//        qDebug()<<"Ctrl被按下,当前ctrlActive："<<ctrlActive;
    }

//    如果是空格键
    if(key_code == Qt::Key_Space){
        spaceActive = !spaceActive;
//        qDebug()<<"Space被释放,当前ctrlActive："<<ctrlActive;
    }
}

void MarkGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    int key_code = event->key();
//    如果是ctrl键
    if(key_code == Qt::Key_Control){
        ctrlActive = !ctrlActive;
//        qDebug()<<"Ctrl被释放,当前ctrlActive："<<ctrlActive;
    }

//    如果是空格键
    if(key_code == Qt::Key_Space){
        spaceActive = !spaceActive;
//        qDebug()<<"Space被释放,当前ctrlActive："<<ctrlActive;
    }


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
    scale(1.0 / DEFAULT_PROPORTION, 1.0 / DEFAULT_PROPORTION);
}

MarkGraphicsView::~MarkGraphicsView()
{

}
