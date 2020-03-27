#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>

#include <widgets/filebutton.h>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();
    void on_importFileButton_clicked();

private slots:

    void on_determine_import_button_clicked();

signals:
//    自定义信号,发送数据给父窗口
    void sendData(QString);

private:
    Ui::ImportDialog *ui;
    FileButton *fileButton;
    QString dirPath ;
};

#endif // IMPORTDIALOG_H
