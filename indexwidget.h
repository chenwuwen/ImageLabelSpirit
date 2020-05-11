#pragma execution_character_set("utf-8")
#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

#include <QWidget>
#include<QFileInfoList>
#include <QFileInfo>
#include <QDebug>
#include <module/createprojectdialog.h>
#include <common/commonutil.h>
namespace Ui {
class IndexWidget;
}

class IndexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IndexWidget(QWidget *parent = nullptr);
    ~IndexWidget();
//    从特定目录(文档目录下的.imagelabelspirit目录下)加载全部项目
    void loadAllProject();

private slots:

    void on_create_project_btn_clicked();
//    完成项目创建
    void compileCreateProject(QString projectName,QString imgPath,QString annotationMeta);

    void on_close_index_widget_btn_clicked();
//    打开项目
    void openProject(QString project_file_path);
//    移除项目
    void removeProjectItem();
private:
    Ui::IndexWidget *ui;
    CreateProjectDialog *createProjectDialog;
};

#endif // INDEXWIDGET_H
