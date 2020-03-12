#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QIcon>
#include <QDebug>
#include <QScreen>

mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);

    //    设置图标( 窗口图标,(操作系统)状态栏图标)
        setWindowIcon(QIcon(":/res/icons/kanyun.png"));
        setWindowTitle("看云图片标注精灵");

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

    //    QGridLayout *g = new QGridLayout;
    //    this->setLayout(g);
    //    g->addWidget(new QPushButton);


        resize(size.width(),size.height());

        qDebug()<<QStringLiteral("主界面显示");
}

mainwidget::~mainwidget()
{
    delete ui;
}
