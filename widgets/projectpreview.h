#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QDebug>

#include <custom/meta.h>
namespace Ui {
class ProjectPreview;
}

class ProjectPreview : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPreview(ProjectInfo project,QWidget *parent = nullptr);
    ~ProjectPreview();

private slots:
    void on_delete_project_btn_clicked();


    void on_operation_project_btn_clicked();

private:
    Ui::ProjectPreview *ui;
};

#endif // PROJECTPREVIEW_H
