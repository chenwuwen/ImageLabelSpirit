#include "settingdialog.h"
#include "ui_settingdialog.h"



SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/setting_dialog_style.qss",this);

    ui->setting_dialog_close_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->setting_dialog_close_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));
//    图片文件夹路径禁止修改
    ui->img_file_path_lineEdit->setEnabled(false);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_setting_dialog_close_btn_clicked()
{
    this->close();
}

void SettingDialog::on_setting_dialog_confirm_btn_clicked()
{
    this->close();
}


void SettingDialog::setImageLocalPath(QString path)
{
    ui->img_file_path_lineEdit->setText(path);
}
