#include "filebutton.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
FileButton::FileButton(QWidget *parent) : QWidget(parent)
{

}

void FileButton::paintEvent(QPaintEvent *){

    qDebug("尺寸[%d,%d]",width(),height());
//     创建画家对象 并指定当前窗口为画图设备
    QPainter p(this);
//    抗锯齿和使用平滑转换算法
//    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPen pen;
//    定义了线条的颜色
    lineColor = lineColor==defaultLineColor?defaultLineColor:lineColor;
    pen.setColor(lineColor);
//    定义了线条的宽度，当设置为线条宽度为0的时候，画笔的宽度一直是1像素宽。如果我们想不显示线条的话,可以设置为-1
    pen.setWidth(lineWidth);
//    apStyle() :设置线条两头的形状，可以是矩形，也可以是圆形的头。通过setCapStyle()设置线条端点形状
    pen.setCapStyle(Qt::RoundCap );


    p.setPen(pen);

//    绘图操作

//    画大矩形
    QRect bigRect = QRect(this->x(),this->y(),this->width(),this->height());
    p.drawRoundRect(bigRect,10,10);

    int maxX = this->x() + this->width();
    int maxY = this->y() + this->height();
    qDebug("maxX: %d,maxY: %d",maxX,maxY);

    int smallX = maxX - (this->width()/5);
    int smallY = this->y();
    int smallWidth = maxX-smallX;
    qDebug("smallX: %d,smallY: %d",smallX,smallY);
    QRect smallRect(smallX,smallY,smallWidth,this->height());

//    画一条竖线
    pen.setWidth(lineWidth/2);
    p.setPen(pen);
    p.drawLine(smallX,smallY,smallX,maxY);

//    设置边框为无边框
    pen.setWidth(-1);
    p.setPen(pen);
//    画小矩形
    p.drawRect(smallRect);

//    文字颜色不能随边框颜色改变而变化
    pen.setColor(Qt::black);
    p.setPen(pen);
//    设置字体的类型，大小，加粗，斜体
    QFont font("Arial",10,QFont::Normal,false);
    p.setFont(font);
//    小矩形中画文字
    p.drawText(smallRect,Qt::AlignVCenter|Qt::AlignCenter,"...");
    if(!pathInfo.isEmpty()){
//        文本过长,将文本截取多余部分显示成省略号
       QString str = fontMetrics().elidedText(pathInfo, Qt::ElideRight,width()-smallWidth );
       p.drawText(bigRect,Qt::AlignVCenter,str);
    }


    //画背景图
//    p.drawPixmap(0,0,width(),height(), QPixmap("C:\\Users\\KANYUN\\Desktop\\5900f3b6ccf32_610.jpg"));
//    p.end();
}

void FileButton::draw_path(QString path){
    pathInfo = path;
//    由于绘图只能在paintEvent方法中进行,因此该函数,只能通过update()方法通知paintEvent()方法执行
    update();

}

 void FileButton::mousePressEvent(QMouseEvent *event){
     {
         qDebug()<< "FileButton被按下";
         // 如果是鼠标左键按下
         if(event->button()==Qt::LeftButton){
             update();
             emit clicked();
         }

     }
 }

 void FileButton::mouseReleaseEvent(QMouseEvent *event){

 }

 void FileButton::mouseMoveEvent(QMouseEvent *event){

 }

 void FileButton::enterEvent(QEvent *){
        lineColor = Qt::green;
        qDebug()<<"鼠标移入事件";
        update();
 }

 void FileButton::leaveEvent(QEvent *){
        lineColor = defaultLineColor;
        qDebug()<<"鼠标移出事件";
        update();
 }
