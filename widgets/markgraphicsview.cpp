#include "markgraphicsview.h"
#define cout qDebug() << "[" <<__FILE__<< " : "<<__LINE__<<"]"

MarkGraphicsView::MarkGraphicsView(QWidget *parent):QGraphicsView(parent)
{
//      设置允许拖拽
      setAcceptDrops(true);
//      缺省鼠标样式
      setCursor(QCursor(Qt::ArrowCursor));
//      隐藏水平/竖直滚动条
      setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//      反锯齿
      setRenderHint(QPainter::Antialiasing);

}


void MarkGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    cout << "MarkGraphicsView类 mousePressEvent方法执行";
}

void MarkGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "MarkGraphicsView类 mouseMoveEvent方法执行";
    if (event->modifiers() == Qt::NoModifier){
        cout << "没有按任何按键,准备画十字线";
//        当键盘没有按任何按键时
        currentMovePoint = event->pos();
//        通知 paintEvent方法画十字线

        drawCrossLine();
        update();
    }

//    如果重构了事件函数,并且需要事件传递,需要添加次方法。
    QGraphicsView::mouseMoveEvent(event);
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
//       防止过小或过大
       if(scaleFactor > 10 || scaleFactor < 0.1 ) return;
//       滚轮的滚动量,正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
       int wheelDeltaValue = event->delta();
       if (wheelDeltaValue > 0){
//            向前滚动，放大;
           this->scale(DEFAULT_PROPORTION, DEFAULT_PROPORTION);
       } else{
//            向后滚动，缩小;
           this->scale(1.0 / DEFAULT_PROPORTION, 1.0 / DEFAULT_PROPORTION);

       }
//      为了改善缩放效果，以鼠标为中心进行缩放
       setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


//      将scene坐标转换为放大缩小后的坐标;
       QPointF viewPoint = this->matrix().map(scenePos);
//      通过滚动条控制view放大缩小后的展示scene的位置;
       horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
       verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));

//      发射缩放比例改变的信号
       emit scaleChange();
       QGraphicsView::wheelEvent(event);
}

void MarkGraphicsView::keyPressEvent(QKeyEvent *event)
{
    int key_code = event->key();
//    如果是ctrl键
    if(key_code == Qt::Key_Control){
        ctrlActive = true;
        qDebug() << "Ctrl被按下,当前ctrlActive："<< ctrlActive;
    }

//    如果是空格键
    if(key_code == Qt::Key_Space){
        spaceActive = true;
        qDebug() << "Space被按下,当前spaceActive："<< spaceActive;
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
//    事件可以被触发
//    在QGraphicsView子类中使用viewport()->setCursor()，才可以真正的改变鼠标的形状。同时，update()也是如此，需要调用viewport()->update()。
//    viewport()->setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsView::enterEvent(event);
}


void MarkGraphicsView::leaveEvent(QEvent *event)
{
//    事件可以被触发
//    在QGraphicsView子类中使用viewport()->setCursor()，才可以真正的改变鼠标的形状。同时，update()也是如此，需要调用viewport()->update()。
//    viewport()->setCursor(QCursor(Qt::ArrowCursor));
    QGraphicsView::leaveEvent(event);
}


void MarkGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "MarkGraphicsView类 dragEnterEvent方法执行";
    event->accept();
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
    for (QGraphicsItem *item : items){
        qDebug() << "重回初始大小";
        int itemType = item->type();
        if(itemType==MarkGraphicsPixmapItem::Type){
           MarkGraphicsPixmapItem *markItem =  dynamic_cast<MarkGraphicsPixmapItem *>(item);
           QSize markItemSize = markItem->getOriginalSize();
           QSize viewportSize = viewport()->size();
           if(markItemSize.width()<viewportSize.width() && markItemSize.height() < viewportSize.height()){
//           会将图元展示到正中央,如果图元比较高,那么展示为图元中间的位置,也就是图片展示的不完整
             centerOn(item);
           }else{
//           使图元充满容器,但是会导致图元变形,因为默认的fitInView方法并不是等比例压缩的(但是可以设置填充方式为等比例),fitview有3个重载的方法,因此可以传入等比压缩的矩形区域来展示
             fitInView(item,Qt::KeepAspectRatio);
           }
        }

    }

}

void MarkGraphicsView::drawCrossLine()
{
    painter = new QPainter(this->viewport());

    pix = new QPixmap(size());
    painter->begin(pix);

    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::red);
    painter->setPen(pen);

    int x = currentMovePoint.x();
    int y = currentMovePoint.y();



//    画十字线

//    绘制横向线
    painter->drawLine(0, y, width(), currentMovePoint.y());
//    绘制纵向线
    painter->drawLine(x, 0, currentMovePoint.x(), height());

//    画坐标信息
    painter->drawText(x+10,y+10,QString("(%1,%2)").arg(x).arg(y));

    painter->end();
}

void MarkGraphicsView::paintEvent(QPaintEvent *event)
{

    QGraphicsView::paintEvent(event);
//    drawCrossLine();
//    QPainter painter(this->viewport());
//    painter.drawPixmap(QPoint(0,0), *pix);

}

MarkGraphicsView::~MarkGraphicsView()
{

}
