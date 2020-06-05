#include "progresswidget.h"
#include "ui_progresswidget.h"


ProgressWidget::ProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressWidget)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    setStyleSheet(QString::fromUtf8("background-color: rgb(195,195,195);"));
    CommonUtil::setQssStyle(QString(":/res/style/progressbar_style.qss"),ui->progress_bar);

//    重设尺寸
    resize(parent->width()*0.2,parent->height() * 0.8);

//    移动至垂直居中
    move(0,parent->height() * 0.1);

//    设置不显示进度条文字
    ui->progress_bar->setTextVisible(false);
//    设置进度条高度
    ui->progress_bar->setFixedHeight(2);

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
