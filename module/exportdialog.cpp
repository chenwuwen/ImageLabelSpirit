#include "exportdialog.h"
#include "ui_exportdialog.h"

#include <common/commonutil.h>

#include <common/fontawesomeicons.h>


#include <widgets/filebutton.h>

#include <mainwidget.h>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QStyle>
#include <QMetaEnum>


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
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->close_export_dialog_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

//    去掉QPushButton阴影
    ui->determine_export_button->setFlat(true);
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

//    按钮组为各个按钮设置id,从而最后得到组内那个按钮被选中
    ui->export_type_button_group->setId(ui->json_btn,export_type::JSON);
    ui->export_type_button_group->setId(ui->xml_btn,export_type::XML);
    ui->export_type_button_group->setId(ui->mongo_btn,export_type::MONGO);

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
    QString dirPath = QFileDialog::getExistingDirectory(this,
                                                        QString("选择文件夹"),
                                                        localPath,QFileDialog::ShowDirsOnly);
    if(!dirPath.isEmpty()){
          localPath = dirPath;
          fileButton->draw_path(localPath);

    }

}

void ExportDialog::setExportLocalPathAndMarkInfoCollection(QString path,QMap<QString,QList<RectMetaInfo>> collection)
{
    qDebug()<< "当前工作路径:"<<path;
    localPath = path;
    fileButton->draw_path(localPath);
    this->markInfoCollection = collection;
}


void ExportDialog::on_determine_export_button_clicked()
{
    QString savePath = localPath.append("/outputs/") ;
    qDebug()<< "最终导出路径:"<< savePath;
//    得到按钮组中被选中的按钮
    int type_id =  ui->export_type_button_group->checkedId();
//    数字转枚举
//    QMetaEnum exportType = QMetaEnum::fromType<export_type>();
    export_type type = static_cast<export_type>(type_id);

//    发射信号
    emit sendExportPathAndExportId(savePath,type);

    this->close();

}
