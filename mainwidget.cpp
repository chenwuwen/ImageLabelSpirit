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

static void initQssFile(QString path,QWidget *widget)
{
    qDebug() << "设置qss样式";
    QFile file(path.arg(QDir::currentPath()));
    file.open(QFile::ReadOnly);
    widget->setStyleSheet(file.readAll());
    file.close();
}


mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
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
    initQssFile(QString(":/res/style/menu_frame_style.qss"),ui->menu_frame);

//    定义按钮
    MenuButton *openDir = new MenuButton(":/res/icons/open.png","打开",ui->menu_frame);
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
    ui->menu_frame->layout()->addWidget(openDir);
    ui->menu_frame->layout()->addWidget(fontButton);
    ui->menu_frame->layout()->addWidget(afterButton);
    ui->menu_frame->layout()->addWidget(settingButton);

    ui->menu_frame->layout()->addWidget(importButton);
    ui->menu_frame->layout()->addWidget(exportButton);


}



mainwidget::~mainwidget()
{
    delete ui;
}
