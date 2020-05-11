#include "projectpreview.h"
#include "ui_projectpreview.h"


ProjectPreview::ProjectPreview(ProjectInfo project,QString projectFilePath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectPreview)
{
    ui->setupUi(this);

    CommonUtil::setQssStyle(":/res/style/project_preview_style.qss",this);
    ui->delete_project_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->delete_project_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

    ui->project_name->setText(project.projectName);
    ui->project_img_path->setText(project.imgPath);
    QDateTime time = QDateTime::fromTime_t(project.createTime.toInt());
//    日期格式化
    ui->project_create_date->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    this->projectFilePath = projectFilePath;

//   ui->operation_project_btn
//    创建一个菜单
    QMenu *operationMenu = new QMenu(this);
    operationMenu->addAction(tr("打开"));
    operationMenu->addAction(tr("重命名"));
//    添加一条分割线
    operationMenu->addAction(tr("删除"));
//    添加菜单
    ui->operation_project_btn->setMenu(operationMenu);
//    设置弹出模式 InstantPopup即为点击按钮立即弹出菜单
    ui->operation_project_btn->setPopupMode(QToolButton::InstantPopup);
//    控制QToolButton按钮的文字和图标如何显示
    ui->operation_project_btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
}



ProjectPreview::~ProjectPreview()
{
    delete ui;
}

void ProjectPreview::mouseDoubleClickEvent(QMouseEvent *event)
{
//    此信号连接到 indexwidget.cpp中的openProject槽函数
    emit mouseDoubleClicked(projectFilePath);
}

void ProjectPreview::on_delete_project_btn_clicked()
{
    qDebug() << "删除project";
    // 创建一个question弹出对话框，添加两个按钮：Yes和Cancel
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Question, tr("提示"), tr("确定要删除项目吗"), QMessageBox::Yes | QMessageBox::Cancel);

    // 将原本显示“Yes”的按钮改为显示“是”
    msgBox->button(QMessageBox::Yes)->setText("确定");

    // 将原本显示“Cancel”的按钮改为显示“否”
    msgBox->button(QMessageBox::Cancel)->setText("取消");

    // 弹出对话框
    int code = msgBox->exec();

    if (code == QMessageBox::No) return;
    QFile file(projectFilePath);
//    移除项目文件
    file.remove();
//    发送删除项目信号给IndexWidget
    emit deleteProjectItem();
}



void ProjectPreview::on_operation_project_btn_clicked()
{

}
