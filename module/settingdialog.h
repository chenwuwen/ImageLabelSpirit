#pragma execution_character_set("utf-8")
#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QStyle>
#include <QDialog>

#include <common/commonutil.h>
#include <common/fontawesomeicons.h>


namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
//    设置图片文件夹路径
    void setImageLocalPath(QString);
//    设置预定义分类
    void setAnnotationMeta(QList<QString>);

private slots:
    void on_setting_dialog_close_btn_clicked();

    void on_setting_dialog_confirm_btn_clicked();

signals:
//    设置改变信号
    void settingChanged(QString);

private:
    Ui::SettingDialog *ui;
    QString annotationMetaStrs;
};

#endif // SETTINGDIALOG_H
