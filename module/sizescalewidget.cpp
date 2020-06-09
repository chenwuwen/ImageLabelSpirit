#include "sizescalewidget.h"
#include "ui_sizescalewidget.h"


SizeScaleWidget::SizeScaleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SizeScaleWidget)
{
    ui->setupUi(this);

    resize(parent->width() * 0.16,parent->height() * 0.4);
    move(parent->width() * 0.8,parent->height() * 0.3);

//    这句必须加,否则该子widget将会是透明的
    setAttribute(Qt::WA_StyledBackground);

    CommonUtil::setQssStyle(QString(":/res/style/size_scale_widget_style.qss"),this);

    initButton();

}

SizeScaleWidget::~SizeScaleWidget()
{
    delete ui;
}

void SizeScaleWidget::initButton()
{
//      得到FontAwesome字体
        QFont font = FontAwesomeIcons::Instance().getFont();

//      放大/缩小/全屏按钮
        ui->narrow_btn->setFlat(true);
        ui->adapt_window_btn->setFlat(true);
        ui->enlarge_btn->setFlat(true);
        ui->adapt_window_btn->setFont(font);
        ui->narrow_btn->setFont(font);
        ui->enlarge_btn->setFont(font);
        ui->adapt_window_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_fullscreen));
        ui->narrow_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_search_minus));
        ui->enlarge_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_search_plus));
}

void SizeScaleWidget::setSizeScale(QString scale)
{
    ui->scale->setText(scale);
}

void SizeScaleWidget::on_enlarge_btn_clicked()
{
//    发送放大图片信号到MainInterface.cpp
    emit enlarge();
}

void SizeScaleWidget::on_narrow_btn_clicked()
{
//    发送缩小图片信号到MainInterface.cpp
    emit narrow();
}

void SizeScaleWidget::on_adapt_window_btn_clicked()
{
//    发送适配窗口尺寸图片信号到MainInterface.cpp
    emit adaptWindow();
}
