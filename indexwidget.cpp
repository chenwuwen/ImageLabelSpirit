#include "indexwidget.h"
#include "ui_indexwidget.h"

#include <widgets/projectpreview.h>

IndexWidget::IndexWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexWidget)
{
    ui->setupUi(this);
    resize(1024,800);
//    配置无边框
    QWidget::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":/res/icons/kanyun.png"));
    setWindowTitle("看云图片标注精灵");
    CommonUtil::setQssStyle(":/res/style/index_widget_style.qss",this);
    ui->close_index_widget_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->close_index_widget_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

    loadAllProject();

}

IndexWidget::~IndexWidget()
{
    delete ui;
}

void IndexWidget::loadAllProject()
{
    QFileInfoList projects = CommonUtil::getProjectInfoList();
    int projectCount = projects.size();
    qDebug() << QString("查找到[%1]个项目").arg(projectCount);
    for(int i = 0;i<projectCount;i++){
        QFileInfo pjFile = projects.at(i);
        Project project = CommonUtil::readProjectInfo(pjFile.absoluteFilePath());
        qDebug() << "得到反序列化的结果：" << project.projectName << "  " << project.annotationMeta;
        ProjectPreview *projectPreview = new ProjectPreview(project);
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole,QVariant::fromValue(project));
//        设置item的内容是自定义的widget
        ui->project_preview_list_widget->setItemWidget(item,projectPreview);

    }
}



void IndexWidget::on_create_project_btn_clicked()
{
    createProjectDialog = new CreateProjectDialog(this);
    connect(createProjectDialog,&CreateProjectDialog::createProject,this,&IndexWidget::compileCreateProject);
    int code = createProjectDialog->exec();
    if (code == QDialog::Accepted){
        loadAllProject();
    }

}

void IndexWidget::compileCreateProject(QString projectName, QString imgPath, QString annotationMeta)
{
//    获取当前时间
    QDateTime time = QDateTime::currentDateTime();
//    将当前时间转为时间戳
    int second = time.toTime_t();
    qDebug() << "新创建的项目信息：" << projectName << "  " << imgPath << "  " << annotationMeta << "  " << QString::number(second);

    Project project;

    project.imgPath = imgPath;
    project.projectName=projectName;
    project.annotationMeta = annotationMeta;
    project.createTime=QString::number(second);
    CommonUtil::saveProjectInfo(project);
}

void IndexWidget::on_close_index_widget_btn_clicked()
{
    this->close();
}
