#include "progresswidget.h"
#include "ui_progresswidget.h"


ProgressWidget::ProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressWidget)
{
    ui->setupUi(this);
//    这句必须加,否则该子widget将会是透明的
    setAttribute(Qt::WA_StyledBackground);
//    因为widget的颜色是半透明的,所以将QLabel的背景颜色设置为透明,这样QLabel就与widget的颜色一样了
    ui->progress_info->setAttribute(Qt::WA_TranslucentBackground, true);
    setStyleSheet(QString::fromUtf8("background-color: rgba(195,195,195,0.9);"));


//    重设尺寸
    resize(parent->width()*0.2,parent->height() * 0.4);

//    移动至垂直居中
    move(0,parent->height() * 0.3);

//    设置不显示进度条文字
    ui->progress_bar->setTextVisible(false);
//    设置进度条高度
    ui->progress_bar->setFixedHeight(2);
//    设置进度条样式
    CommonUtil::setQssStyle(QString(":/res/style/progressbar_style.qss"),ui->progress_bar);

//  进度条文本颜色
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::green);
    ui->progress_bar->setPalette(palette);

}

ProgressWidget::~ProgressWidget()
{
    delete ui;
}

void ProgressWidget::setProgressInfo(QString info, int imgCount, int hasMarkCount)
{
    ui->progress_info->setText(info);
//    设置进度条最大值
    ui->progress_bar->setMaximum(imgCount);
//    设置进度条当前的运行值
    ui->progress_bar->setValue(hasMarkCount);
}
