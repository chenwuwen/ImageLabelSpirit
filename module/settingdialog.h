#pragma execution_character_set("utf-8")
#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();


public slots:
//    设置图片文件夹路径
    void setImageLocalPath(QString);

private slots:
    void on_setting_dialog_close_btn_clicked();

    void on_setting_dialog_confirm_btn_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
