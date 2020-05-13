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
#include <QInputDialog>
#include <QLineEdit>
#include <QMouseEvent>

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
//    鼠标移入事件
    void enterEvent(QEvent *);
//    鼠标移出事件
    void leaveEvent(QEvent *);
private slots:
    void on_delete_project_btn_clicked();
//    重命名项目名(注意写在槽函数下,因为这个函数是由QMenu中的Action调用的)
    void renameProject();
signals:
//    双击窗体触发打开当前项目信号
    void openCurrentProject(QString project_file_path);
//    删除项目信号
    void deleteProjectItem();
//    项目名称更改信息
    void projectNameModify(QString newProjectName);

private:
    Ui::ProjectPreview *ui;
    QString projectFilePath;
    ProjectInfo currentProject;
};

#endif // PROJECTPREVIEW_H
