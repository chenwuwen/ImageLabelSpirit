#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"



CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);
    resize(parent->width() * 0.8,parent->height() * 0.8);
//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("创建项目");
    CommonUtil::setQssStyle(":/res/style/create_project_dialog_style.qss",this);
    ui->close_create_project_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->close_create_project_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

//    去掉QPushButton阴影
    ui->determine_create_project_btn->setFlat(true);

    QLayout *verticalLayout = new QVBoxLayout(ui->create_project_file_widget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    fileButton  = new FileButton(ui->create_project_file_widget);
    fileButton->setObjectName(QString::fromUtf8("create_project_file_btn"));
    verticalLayout->addWidget(fileButton);

    connect(fileButton,&FileButton::clicked,this,&CreateProjectDialog::on_create_project_file_btn_clicked);
}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

void CreateProjectDialog::on_determine_create_project_btn_clicked()
{
    QString project_name = ui->project_name_lineedit->text();
    QString project_meta =ui->project_annotation_meta_lineedit->text();
    if (project_name.isEmpty() || dirPath.isEmpty()) return;
    emit createProject(project_name,dirPath,project_meta);
    this->accept();
}

void CreateProjectDialog::on_close_create_project_btn_clicked()
{
    this->reject();
}




void CreateProjectDialog::on_create_project_file_btn_clicked()
{
//    文件夹选择对话框是使用getExistingDirectory()函数 来自头文件QFileDialog
//    第一个参数 父对象（一般是this）
//    第二个参数 对话框标题
//    第三个参数 对话框开始目录
//    第四个参数 默认是只显示目录 如果要别的参数可以参考以下表格 https://doc.qt.io/qt-5/qfiledialog.html#Option-enum
    dirPath = QFileDialog::getExistingDirectory(this,
                                                QString("选择文件夹"),
                                                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                QFileDialog::ShowDirsOnly);
    fileButton->draw_path(dirPath);
}
