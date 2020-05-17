#include "exportmessagebox.h"
#include "ui_exportmessagebox.h"

ExportMessageBox::ExportMessageBox(QString dir,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportMessageBox)
{
    ui->setupUi(this);
    this->dirPath = dir;
//    配置无边框 (副作用：窗口将无法移动需要重写mousePressEvent和mouseMoveEvent来实现移动窗口)
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/export_message_box_style.qss",this);
    ui->export_message_box_close_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->export_message_box_close_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

//    去掉QPushButton阴影
    ui->review_export_result_btn->setFlat(true);
//    设置进度条最小高度
    ui->export_progress_bar->setMinimumHeight(30);
//       设置进度条范围
    ui->export_progress_bar->setRange(0,100);
//    设置进度条当前进度方向为水平方向
    ui->export_progress_bar->setOrientation(Qt::Horizontal);
    ui->export_progress_bar->setFormat("%p%");
//    设置文本对齐方式
    ui->export_progress_bar->setAlignment(Qt::AlignCenter);
//    设置进度条文本可见
    ui->export_progress_bar->setTextVisible(true);
//    设置当前进度条进度
    ui->export_progress_bar->setValue(0);
//    默认禁用查看按钮
    ui->review_export_result_btn->setEnabled(false);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
//    200毫秒更新一次
    timer->start(200);
}

ExportMessageBox::~ExportMessageBox()
{
    delete ui;
}

void ExportMessageBox::export_complete()
{
//    启用查看按钮
    ui->review_export_result_btn->setEnabled(true);
//    设置进度条为100
    ui->export_progress_bar->setValue(100);
//    停掉定时器
    timer->stop();
}

void ExportMessageBox::on_export_message_box_close_btn_clicked()
{
       this->close();
}



void ExportMessageBox::on_review_export_result_btn_clicked()
{
    qDebug() << "打开导出的文件夹路径：" << dirPath ;
//    打开文件夹 https://zhuanlan.zhihu.com/p/33578217
    QDesktopServices::openUrl(QUrl("file:"+ dirPath,QUrl::TolerantMode));
    this->close();
}

void ExportMessageBox::updateProgress()
{
    static int current_progress = 0;
    current_progress++;
    if (current_progress > 80){
        timer->stop();
    }else{
        ui->export_progress_bar->setValue(current_progress);
    }
}

void ExportMessageBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        last_mouse_position = event->globalPos();
    }

}

void ExportMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton)){
        return;
    }

    const QPoint position = pos() + event->globalPos() - last_mouse_position;
    move(position.x(), position.y());
    last_mouse_position = event->globalPos();

}

void ExportMessageBox::mouseReleaseEvent(QMouseEvent *event)
{

}
