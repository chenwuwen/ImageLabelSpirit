#include "settingdialog.h"
#include "ui_settingdialog.h"



SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    resize(parent->width() * 0.4,parent->height() * 0.5);

//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/setting_dialog_style.qss",this);

//    图片文件夹路径禁止修改
    ui->img_file_path_lineEdit->setEnabled(false);

//    创建关闭窗口按钮
    QPushButton *setting_dialog_close_btn = new QPushButton(ui->widget);
    setting_dialog_close_btn->setObjectName("setting_dialog_close_btn");
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    setting_dialog_close_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));
    setting_dialog_close_btn->setText("");
    setting_dialog_close_btn->setFixedSize(QSize(ui->widget->height(),ui->widget->height()));
    setting_dialog_close_btn->setFlat(true);
    setting_dialog_close_btn->stackUnder(this);
    setting_dialog_close_btn->move(this->width() - setting_dialog_close_btn->width(),0);
    setting_dialog_close_btn->show();
    connect(setting_dialog_close_btn,&QPushButton::clicked,this,&SettingDialog::on_setting_dialog_close_btn_clicked);
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
//    这里要判断getText是否合法
    QString getText = ui->classification_lineEdit->text();

    if ( getText != annotationMetaStrs){
        emit settingChanged(getText);
    }
    this->close();
}


void SettingDialog::setImageLocalPath(QString path)
{
    ui->img_file_path_lineEdit->setText(path);
}

void SettingDialog::setAnnotationMeta(QList<QString> annatationMetaList)
{
//    将QList<QString>中的各个值,以逗号形式分隔组成新的字符串
    QString str = annatationMetaList.join(",");
    ui->classification_lineEdit->setText(str);
    this->annotationMetaStrs = str;
}


