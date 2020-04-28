#include "projectpreview.h"
#include "ui_projectpreview.h"

#include <QDateTime>

ProjectPreview::ProjectPreview(ProjectInfo project,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectPreview)
{
    ui->setupUi(this);
    ui->project_name->setText(project.projectName);
    ui->project_img_path->setText(project.imgPath);
    QDateTime time = QDateTime::fromTime_t(project.createTime.toInt());
    ui->project_create_date->setText(time.toString());
}



ProjectPreview::~ProjectPreview()
{
    delete ui;
}

void ProjectPreview::on_delete_project_btn_clicked()
{
    qDebug() << "删除project";
}



void ProjectPreview::on_operation_project_btn_clicked()
{

}
