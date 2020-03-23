#include "bform.h"
#include "mainwidget.h"

#include "ui_mainwidget.h"
#include <widgets/menubutton.h>

#include <QIcon>
#include <QDebug>
#include <QScreen>
#include <QGridLayout>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
/**
  设置widget的样式
 * @brief setQssStyle
 * @param path  资源文件 :/** 形式
 * @param widget  哪个widget
 */
static void setQssStyle(QString path,QWidget *widget)
{
    qDebug() << "设置qss样式";
    QFile file(path);
    file.open(QFile::ReadOnly);
    widget->setStyleSheet(file.readAll());
    file.close();
}


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);


    //    设置图标( 窗口图标,(操作系统)状态栏图标)
    qDebug()<<"重新设置窗体标题/图标";
    setWindowIcon(QIcon(":/res/icons/kanyun.png"));
    setWindowTitle("看云图片标注精灵");
    //    隐藏标题栏
    //    setWindowFlags(Qt::SplashScreen);

    //     获取桌面信息
    //     QDesktopWidget* desktopWidget = QApplication::desktop();
    //     获取可用桌面大小
    //     QRect deskRect = desktopWidget->availableGeometry();
    //     resize(deskRect.width(),deskRect.height());

    //     获取设备屏幕大小(方法已经过时)
    //     QRect screenRect = desktopWidget->screenGeometry();
    //     resize为虚函数，需要在层序中重写（重新实现）
    //     resize(screenRect.width(),screenRect.height());

    //    推荐的方法
    QList<QScreen *> screens = QGuiApplication::screens();
    QScreen* screen = screens.first();
    QSize size = screen->size();

    qDebug()<<"重新设置窗体大小";
    resize(size.width(),size.height());

    //    QGridLayout *g = new QGridLayout;
    //    this->setLayout(g);
    //    g->addWidget(new QPushButton);



    //     禁止拖动窗口大小
    //    setFixedSize(this->width(),this->height());
    //    禁止最大化按钮
    //    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    //=======这些已在Qt 设计师中设计了===========

    //    定义栅格化布局
    //    QGridLayout *mainLayout = new QGridLayout;
    //    左侧菜单组件
    //    QWidget *leftMenuWidget = new QWidget;
    //    右侧标注信息组件
    //    QWidget *rightAnnoctionWidget = new QWidget;
    //    下侧文件信息组件
    //    QWidget *bottomWidget = new QWidget;
    //    中间住面板组件
    //    QWidget *centerWidget = new QWidget;

    //    设置原始方向
    //    mainLayout->setOriginCorner(Qt::Corner);

    //    获取列数
    //    int columnCount = mainLayout->columnCount();
    //    获取行数
    //   int rowCount = mainLayout->rowCount();

    //    qDebug()<<"行数："<<rowCount<<"列数："<<columnCount;

    //    mainLayout->addWidget(leftMenuWidget,0,0,-1,2,Qt::AlignLeft);
    //    mainLayout->addWidget(rightAnnoctionWidget,0,0,-1,2,Qt::AlignRight);

    //    设置布局为栅格化布局
    //    setLayout(mainLayout);

    // =======这些已在Qt 设计师中设计了===========
    setQssStyle(QString(":/res/style/menu_frame_style.qss"),ui->menu_frame);
    setQssStyle(QString(":/res/style/annotation_frame_style.qss"),ui->annotation_frame);
    setQssStyle(QString(":/res/style/file_frame_style.qss"),ui->file_frame);
    setQssStyle(QString(":/res/style/progressbar_style.qss"),ui->progressBar);

    //    定义按钮
    MenuButton *openDirButton = new MenuButton(":/res/icons/open.png","新建",ui->menu_frame);
    MenuButton *fontButton = new MenuButton(":/res/icons/font.png","前一个",ui->menu_frame);
    MenuButton *afterButton = new MenuButton(":/res/icons/after.png","后一个",ui->menu_frame);
    MenuButton *settingButton = new MenuButton(":/res/icons/setting.png","设置",ui->menu_frame);
    MenuButton *moveButton = new MenuButton(":/res/icons/move.png","移动",ui->menu_frame);
    MenuButton *importButton = new MenuButton(":/res/icons/import.png","导入",ui->menu_frame);
    MenuButton *exportButton = new MenuButton(":/res/icons/export.png","导出",ui->menu_frame);
    //    分隔线
    QFrame * line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    //    将按钮添加进menu_frame中
    ui->menu_frame->layout()->addWidget(moveButton);
    ui->menu_frame->layout()->addWidget(line);
    ui->menu_frame->layout()->addWidget(openDirButton);
    ui->menu_frame->layout()->addWidget(fontButton);
    ui->menu_frame->layout()->addWidget(afterButton);
    ui->menu_frame->layout()->addWidget(settingButton);

    ui->menu_frame->layout()->addWidget(importButton);
    ui->menu_frame->layout()->addWidget(exportButton);

    //    设置按钮对象的名称方便后续可以根据组件名称写槽函数(利用QMetaObject::connectSlotsByName(QObject *o)),而不必每个按钮都去写connect()函数
    //    原来想的是通过规范命名,即可不必再写connect()连接函数,结果对于自定义的控件来说,并不能实现,需要注意,因此还需要手动写connect()函数
    openDirButton->setObjectName(QString::fromUtf8("openDirButton"));
    fontButton->setObjectName(QString::fromUtf8("fontButton"));
    afterButton->setObjectName(QString::fromUtf8("afterButton"));
    settingButton->setObjectName(QString::fromUtf8("settingButton"));
    moveButton->setObjectName(QString::fromUtf8("moveButton"));
    importButton->setObjectName(QString::fromUtf8("importButton"));
    exportButton->setObjectName(QString::fromUtf8("exportButton"));

    qDebug()<< ui->menu_frame->width()<<ui->file_frame->height();
    // ui->menu_frame->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //    定义连接函数
    connect(openDirButton,&MenuButton::clicked,this,&MainWidget::on_openDirButton_clicked);

}



MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_clicked()
{
    QPushButton *b;
    QMessageBox::critical(NULL, "critical", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

}

void MainWidget::on_importButton_clicked()
{
    QFile file;
//    定义文件对话框
//    第一个参数parent，用于指定父组件。注意，很多Qt组件的构造函数都会有这么一个parent参数，并提供一个默认值0；
//    第二个参数caption，是对话框的标题；
//    第三个参数dir，是对话框显示时默认打开的目录 ：https://www.bbsmax.com/A/A2dmQLn7de/
//    第四个参数filter，是对话框的后缀名过滤器
//    第五个参数selectedFilter，是默认选择的过滤器
//    第六个参数options，是对话框的一些参数设定，比如只显示文件夹等等，它的取值是enum QFileDialog::Option，每个选项可以使用 | 运算组合起来
    QString f = QFileDialog::getOpenFileName(this, QString("选择文件"),QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),QString("TEXT(*.txt)"));
    file.setFileName(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray t ;
        while(!file.atEnd())
        {
            t += file.readLine();
        }
        file.close();
    }
}

void MainWidget::on_openDirButton_clicked()
{
//    文件夹选择对话框是使用getExistingDirectory()函数 来自头文件QFileDialog
//    第一个参数 父对象（一般是this）
//    第二个参数 对话框标题
//    第三个参数 对话框开始目录
//    第四个参数 默认是只显示目录 如果要别的参数可以参考以下表格 https://doc.qt.io/qt-5/qfiledialog.html#Option-enum
    QString dirPath = QFileDialog::getExistingDirectory(this, QString("选择文件夹"),
                                                  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                  QFileDialog::ShowDirsOnly);

    if(!dirPath.isEmpty()){
        QDir dir(dirPath);
        QStringList nameFilters;
        nameFilters<<"*.jpg" << "*.png";
        QList<QString> files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        qDebug()<<files;
        QStandardItem *item;
        imgFilesItemModel->setRowCount(files.size());
        imgFilesItemModel->setColumnCount(1);
        for (QString img: files) {
             qDebug()<<img;
//             创建item
             item=new QStandardItem(img);
             imgFilesItemModel->appendRow(item);
        }
    }
    ui->file_list_view->setModel(imgFilesItemModel);

}
