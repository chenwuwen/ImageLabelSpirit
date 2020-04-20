#pragma execution_character_set("utf-8")
#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

#include <widgets/filebutton.h>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();


public slots:
    void on_close_export_dialog_btn_clicked();
    void on_exportFileButton_clicked();
    void setExportLocalPath(QString);

private slots:
    void on_determine_export_button_clicked();

private:
    Ui::ExportDialog *ui;
    FileButton *fileButton;
//    父窗口传过来的路径值
    QString localPath;
};

#endif // EXPORTDIALOG_H
