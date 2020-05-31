#include "menubutton.h"


MenuButton::MenuButton(QWidget *parent):QPushButton(parent)
{

}
MenuButton::MenuButton(QString img,QString text,bool check_able,QWidget *parent):QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
    this->img=img;
    this->text=text;
    this->setCheckable(check_able);
//    设置控件qss样式
    setStyleSheet(CommonUtil::readQssFile(":/res/style/menubutton_style.qss"));
//    去掉QPushButton默认的边框,与qss配置使用才能达到无边框目的
    setFlat(true);
//    构造函数中,即使传递了parent,其布局也为空,打印结果为QObject(0x0)
//    qDebug()<<"默认布局："<<this->layout();
}


void MenuButton::paintEvent(QPaintEvent *event)
{


//    定义画家
    QPainter p(this);

//    下面三行代码解决了,QT自定义控件为自定义控件设置QSS无效:https://blog.csdn.net/wumingzcj/article/details/79130705
    QStylePainter sp(this);
    QStyleOptionButton opt;
    initStyleOption(&opt);
    sp.drawControl(QStyle::CE_PushButton,opt);

//    定义矩形大小
    int width,height;

    QPixmap pixmap;
    pixmap.load(img);
//    得到背景图片大小
    QSize imgSize = pixmap.size();
    int imgWidth = imgSize.width();
    int imgHeight = imgSize.height();


//    qDebug()<<"图片大小"<<imgSize;
//    计算文字大小
    QFontMetrics fm = p.fontMetrics();
    int textWidth = fm.width(text);
    int textHeight = fm.ascent()+fm.descent();
//    qDebug("文字大小:[%d,%d]",textWidth,textHeight);

//    最终画图矩形的尺寸
    width = imgWidth>textWidth?imgWidth:textWidth;
    height = imgHeight + textHeight;

    width = height>width?height:width;

//    添加padding内边距
    width += defaultPadding*2;
    height += defaultPadding*2;

//    qDebug("最终矩形大小:[%d,%d]",width,height);

//    这里添加resize,是因为该类继承自QPushButton类,如果最终矩形的长宽大于30(测试得出),那么矩形将显示不完整
//    如果继承的是QWidget类,那么则无需此设置,猜测是由于QPushButton默认配置了大小,
//    resize的大小应该比要画的矩形的大小大一个边框的宽度

    resize(width+1,height+1);
    setContentsMargins(0,0,0,0);
    QRect rect = QRect(0,0,width,height);
//    画矩形实际是不需要画出来的
//    p.drawRect(rect);

//    画图片
    p.drawPixmap((width-imgWidth)/2,defaultPadding,imgWidth,imgHeight,pixmap);
//    画文字
    QRectF textRectf = QRectF(0,imgHeight,width,height-imgHeight-defaultPadding);
    p.drawText(textRectf,Qt::AlignCenter,text);

//    上面画了一个背景图和文字,他们的内边距至少是defaultPadding

//    挪动位置,使按钮居中
    movePosition();
}


//void MenuButton::nextCheckState()
//{
//    qDebug() << "MenuButton nextCheckState()方法执行";
//    if (!isChecked()){
//        qDebug() << "由于MenuButton是未选中状态,因此设置为选中状态";
//        setChecked(!isChecked());
//    }else{
//        setChecked(!isChecked());
//    }
//}

MenuButton::~MenuButton()
{
    qDebug() << "MenuButton析构函数执行";
}

void MenuButton::movePosition()
{
    QWidget *p = this->parentWidget();
    QLayout *layout =  p->layout();
    int rx = this->x();
    int ry = this->y();
   if(layout != NULL){
//    得到layout对象的类名
      QString layoutName = layout->metaObject()->className();
      if(layoutName == "QVBoxLayout"){
          rx = (p->width() - width())/2;
          ry = this->y();
      }

      if(layoutName == "QHBoxLayout"){
          rx = this->x();
          ry = (p->height() - height())/2;
      }

      move(rx,ry);
   }
}

