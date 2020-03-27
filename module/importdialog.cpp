
#include "importdialog.h"
#include "ui_importdialog.h"

#include <QFileDialog>
#include <QStandardPaths>

#include <common/commonutil.h>

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
//    配置无边框
//    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/import_dialog_style.qss",this);
//    去掉QPushButton阴影
//    ui->determine_import_button->setFlat(true);
    fileButton  = new FileButton(ui->file_button_widget);
    fileButton->setObjectName(QString::fromUtf8("import_file_button"));
    connect(fileButton,&FileButton::clicked,this,&ImportDialog::on_importFileButton_clicked);

}

ImportDialog::~ImportDialog()
{
    delete ui;
}


void ImportDialog::on_importFileButton_clicked(){
    QFile file;
//    定义文件对话框
//    第一个参数parent，用于指定父组件。注意，很多Qt组件的构造函数都会有这么一个parent参数，并提供一个默认值0；
//    第二个参数caption，是对话框的标题；
//    第三个参数dir，是对话框显示时默认打开的目录 ：https://www.bbsmax.com/A/A2dmQLn7de/
//    第四个参数filter，是对话框的后缀名过滤器
//    第五个参数selectedFilter，是默认选择的过滤器
//    第六个参数options，是对话框的一些参数设定，比如只显示文件夹等等，它的取值是enum QFileDialog::Option，每个选项可以使用 | 运算组合起来
//    QString f = QFileDialog::getOpenFileName(this, QString("选择文件"),QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),QString("TEXT(*.txt)"));
//    file.setFileName(f);
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QByteArray t ;
//        while(!file.atEnd())
//        {
//            t += file.readLine();
//        }
//        file.close();

//    }

    dirPath = QFileDialog::getExistingDirectory(this, QString("选择文件夹"),
                                                  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                  QFileDialog::ShowDirsOnly);
    fileButton->draw_path(dirPath);


}


void ImportDialog::on_determine_import_button_clicked()
{
    if(!dirPath.isEmpty()){
        emit sendData(dirPath);
        this->close();
    }

}