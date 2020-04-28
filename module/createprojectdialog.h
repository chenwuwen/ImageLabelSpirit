#pragma execution_character_set("utf-8")
#ifndef CREATEITEMDIALOG_H
#define CREATEITEMDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QStyle>
#include <common/commonutil.h>

#include <widgets/filebutton.h>

#include <QFileDialog>
#include <QStandardPaths>

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProjectDialog(QWidget *parent = nullptr);
    ~CreateProjectDialog();

signals:
    void createProject(QString projectName,QString imgPath,QString annotationMeta);

private slots:
    void on_determine_create_project_btn_clicked();

    void on_close_create_project_btn_clicked();

    void on_create_project_file_btn_clicked();

private:
    Ui::CreateProjectDialog *ui;
    QString dirPath;
    FileButton *fileButton;
};

#endif // CREATEITEMDIALOG_H
