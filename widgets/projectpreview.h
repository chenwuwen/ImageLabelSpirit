#pragma execution_character_set("utf-8")
#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QStyle>
#include <QToolButton>
#include <QMenu>
#include <QMessageBox>
#include <common/commonutil.h>
#include <custom/meta.h>
namespace Ui {
class ProjectPreview;
}

class ProjectPreview : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPreview(ProjectInfo project,QString projectFilePath,QWidget *parent = nullptr);
    ~ProjectPreview();
protected:
//    鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void on_delete_project_btn_clicked();


    void on_operation_project_btn_clicked();
signals:
//    双击窗体触发信号
    void mouseDoubleClicked(QString project_file_path);
//    删除项目信号
    void deleteProjectItem();

private:
    Ui::ProjectPreview *ui;
    QString projectFilePath;
};

#endif // PROJECTPREVIEW_H
