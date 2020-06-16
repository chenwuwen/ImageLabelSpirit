#include "exportdialog.h"
#include "ui_exportdialog.h"




ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    resize(parent->width() * 0.4,parent->height() * 0.4);

//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("导入文件");
    CommonUtil::setQssStyle(":/res/style/export_dialog_style.qss",this);


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

//    禁用Mongo导出方式,主要是未实现Mongo导出方式
    ui->mongo_btn->setEnabled(false);

//    默认json为选中状态
    ui->json_btn->setChecked(true);

//    按钮组为各个按钮设置id,从而最后得到组内那个按钮被选中
    ui->export_type_button_group->setId(ui->json_btn,export_type::JSON);
    ui->export_type_button_group->setId(ui->xml_btn,export_type::XML);
    ui->export_type_button_group->setId(ui->mongo_btn,export_type::MONGO);

//    创建关闭窗口按钮
    QPushButton *close_export_dialog_btn = new QPushButton(ui->head_widget);
    close_export_dialog_btn->setObjectName("close_export_dialog_btn");
    close_export_dialog_btn->setFlat(true);

    close_export_dialog_btn->setFixedSize(QSize(ui->head_widget->height(),ui->head_widget->height()));
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    close_export_dialog_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));
    close_export_dialog_btn->setText("");
    close_export_dialog_btn->show();
    close_export_dialog_btn->move(this->width() - close_export_dialog_btn->width(),0);
    close_export_dialog_btn->stackUnder(this);
//    创建关闭窗口按钮信号与槽函数的连接
    connect(close_export_dialog_btn,&QPushButton::clicked,this,&ExportDialog::on_close_export_dialog_btn_clicked);

}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_close_export_dialog_btn_clicked()
{
//   直接关闭窗口
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

//    使用QDialog::Accepted的返回值关闭窗口
    this->accept();

}

void ExportDialog::on_push_btn_clicked()
{
    QMessageBox::information(this,"提示","这个具体上传到哪里我还不确定,"
                                       "作为开源的软件希望可以上传到公共空间,不需要注册什么的。"
                                       "理想化的状态是,上传完成之后。返回取数据的连接+提取码。"
                                       "一方面降低使用成本,另一方面又能保证数据安全。其次上传的文件,我认为应该是"
                                       ".ils 格式的文件,下载完成后放到用户家目录下的.imagelablespirit文件中。"
                                       "所以下载数据的操作是否应该由软件本身提供？(当然也要支持浏览器下载,因为需要考虑弱网无网环境),"
                                       "这样就不必担心使用者再创建目录,并复制数据了。所以,找到一个合适公共存储是一个值得深思的问题！"
                                       );
}
