#include "exportdialog.h"
#include "ui_exportdialog.h"

#include <common/commonutil.h>

#include <common/fontawesomeicons.h>


#include <widgets/filebutton.h>

#include <mainwidget.h>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/export_dialog_style.qss",this);
    ui->close_export_dialog_btn->setFlat(true);
    QFont font =  FontAwesomeIcons::Instance().getFont();
    ui->close_export_dialog_btn->setFont(font);
    ui->close_export_dialog_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_close));

    //    去掉QPushButton阴影
//    ui->determine_export_button->setFlat(true);
    QLayout *verticalLayout = new QVBoxLayout(ui->file_button_widget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    fileButton  = new FileButton(ui->file_button_widget);
    fileButton->setObjectName(QString::fromUtf8("export_file_button"));
    verticalLayout->addWidget(fileButton);
    connect(fileButton,&FileButton::clicked,this,&ExportDialog::on_exportFileButton_clicked);


    ui->json_btn->setCheckable(true);
    ui->xml_btn->setCheckable(true);
    ui->mongo_btn->setCheckable(true);

//    默认json为选中状态
    ui->json_btn->setChecked(true);



}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_close_export_dialog_btn_clicked()
{
    this->close();
}

void ExportDialog::on_exportFileButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, QString("选择文件夹"),
                                                  localPath,
                                                  QFileDialog::ShowDirsOnly);
    if(!dirPath.isEmpty()){
          localPath = dirPath;
          fileButton->draw_path(localPath);

    }

}

void ExportDialog::setExportLocalPath(QString path)
{
    qDebug()<< "当前工作路径:"<<path;
    localPath = path;
    fileButton->draw_path(localPath);
}

void ExportDialog::on_determine_export_button_clicked()
{
    qDebug()<< "最终导出路径:"<< localPath;
}
