#include "markgraphicspixmapitem.h"
#define cout qDebug() << "[" << __FILE__ << " : " <<  __LINE__ << "]"

//QGraphicsItem的mouseMoveEvent()函数必须鼠标按下的情况下进行move才会触发。
//QWidget的mouseMoveEvent()函数可以通过设置setMouseTracking(true)在鼠标不需要按下的情况下，触发鼠标move事件。
//QGraphicsItem要实现鼠标不按下的情况下，获取鼠标move事件，可通过QGraphicsItem::setAcceptHoverEvents ()来实现，可通过设置setAcceptHoverEvents(true)使其生效
//打开这个选项，就可以接收到以下事件了hoverEnterEvent(), hoverMoveEvent(), and hoverLeaveEvent().

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    获得拖拽支持
    setAcceptDrops(true);
//    可选择
//    setFlags(QGraphicsItem::ItemIsSelectable);
//    可移动
    setFlags(QGraphicsItem::ItemIsMovable);
//    图形项默认无法接收悬停事件，可以使用QGraphicsItem的setAcceptHoverEvents()函数使图形项可以接收悬停事件。
    setAcceptHoverEvents(true);
//    一个拥有焦点(focus)的QWidget才可以接受键盘事件,不设置无法响应keyPressEvent/keyReleaseEvent事件
    setFlag(QGraphicsItem::ItemIsFocusable);

}

MarkGraphicsPixmapItem::MarkGraphicsPixmapItem(const QString imgPath, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    QPixmap pixmap;
    pixmap.load(imgPath);
    setPixmap(pixmap);
    currentPixmap = pixmap;
//    获得拖拽支持
    setAcceptDrops(true);
//    可选择
//    setFlags(QGraphicsItem::ItemIsSelectable);
//   可移动
    setFlags(QGraphicsItem::ItemIsMovable);
//    图形项默认无法接收悬停事件，可以使用QGraphicsItem的setAcceptHoverEvents()函数使图形项可以接收悬停事件。
    setAcceptHoverEvents(true);
//    一个拥有焦点(focus)的QWidget才可以接受键盘事件
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void MarkGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "MarkGraphicsPixmapItem类的 mouseMoveEvent() 方法执行";
    endScenePoint = mapToScene(event->pos());
//    event->modifiers() 返回发送事件时使用的键盘修饰符。但是数量有限,仅有几个可用字符按键
    if(spaceActive) {
//      如果是空格键按下状态鼠标移动则是拖拽事件
        qreal xInterval = endScenePoint.x() - startScenePoint.x();
        qreal yInterval = endScenePoint.y() - startScenePoint.y();
        QPointF moveToPoint = startPixmapItemPoint + QPointF(xInterval,yInterval);
        setPos(moveToPoint);
    }
    QGraphicsItem::mouseMoveEvent(event);
}


void MarkGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MarkGraphicsPixmapItem类 的 mousePressEvent() 方法执行";
    QGraphicsItem::mousePressEvent(event);
    if (spaceActive && event->button() == Qt::LeftButton){
        startPixmapItemPoint = event->pos();
        startScenePoint = mapToScene(startPixmapItemPoint);
    }
}

void MarkGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 mouseReleaseEvent() 方法执行";
    QGraphicsItem::mouseReleaseEvent(event);
}




void MarkGraphicsPixmapItem::keyPressEvent(QKeyEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 keyPressEvent() 方法执行";
    if (event->key()  == Qt::Key_Space) spaceActive = true;
//    空格键按下时判断图元是否获取焦点,来设置鼠标形状
    if (spaceActive && hasFocus()){
        setCursor(QCursor(Qt::OpenHandCursor));
    }
    QGraphicsPixmapItem::keyPressEvent(event);
}

void MarkGraphicsPixmapItem::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "MarkGraphicsPixmapItem类 的 keyReleaseEvent() 方法执行";
    if (event->key()  == Qt::Key_Space) {
        spaceActive = false;
        setCursor(QCursor(Qt::ArrowCursor));
    }
    QGraphicsPixmapItem::keyReleaseEvent(event);
}

void MarkGraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "MarkGraphicsPixmapItem类 的 hoverEnterEvent() 方法执行";
//    鼠标进入时判断空格键状态设置鼠标形状
    if (spaceActive){
        qDebug() << "设置鼠标形状为手型" ;
        setCursor(QCursor(Qt::OpenHandCursor));
    }
}

void MarkGraphicsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<< "MarkGraphicsPixmapItem类 的 hoverLeaveEvent() 方法执行";
    setCursor(Qt::ArrowCursor);
}

void MarkGraphicsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<< "MarkGraphicsPixmapItem类 的 hoverMoveEvent() 方法执行";
}

QSize MarkGraphicsPixmapItem::getOriginalSize()
{
    return currentPixmap.size();
}

void MarkGraphicsPixmapItem::setSpaceActive(bool state)
{
    spaceActive = state;
}
