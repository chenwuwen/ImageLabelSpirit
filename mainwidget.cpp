
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
#include <QGraphicsRectItem>

#include <common/commonutil.h>

#include <module/exportdialog.h>
#include <module/importdialog.h>





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
//        setWindowFlags(Qt::SplashScreen);
//        setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);

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
//    QList<QScreen *> screens = QGuiApplication::screens();
//    QScreen* screen = screens.first();
//    QSize size = screen->size();

    qDebug()<<"重新设置窗体大小";

//    最大化显示函数(相当于点了最大化按钮)
    showMaximized();
//    实例化QStandardItemModel
    imgFilesItemModel = new QStandardItemModel;

//      全屏显示函数 此函数将导致窗口占满屏幕且不显示系统状态栏
//    showFullScreen();


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
    CommonUtil::setQssStyle(QString(":/res/style/menu_frame_style.qss"),ui->menu_frame);
    CommonUtil::setQssStyle(QString(":/res/style/annotation_frame_style.qss"),ui->annotation_frame);
    CommonUtil::setQssStyle(QString(":/res/style/file_frame_style.qss"),ui->file_frame);
    CommonUtil::setQssStyle(QString(":/res/style/main_frame_style.qss"),ui->main_frame);
    CommonUtil::setQssStyle(QString(":/res/style/progressbar_style.qss"),ui->progress_bar);
//    进度条文本颜色
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::green);
    ui->progress_bar->setPalette(palette);

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
    connect(settingButton,&MenuButton::clicked,this,&MainWidget::on_settingButton_clicked);
    connect(moveButton,&MenuButton::clicked,this,&MainWidget::on_moveButton_clicked);
    connect(importButton,&MenuButton::clicked,this,&MainWidget::on_importButton_clicked);
    connect(exportButton,&MenuButton::clicked,this,&MainWidget::on_exportButton_clicked);
//    下面两个连接函数使用了lambda表达式
    connect(fontButton,&MenuButton::clicked,this,[=]{
        qDebug() << "前一个按钮被点击";
        if(currentImg>0){
            currentImg--;   
        }else{
            currentImg = imgCount-1;
        }
        setProcessInfo();
        displayImg();
    });
    connect(afterButton,&MenuButton::clicked,this,[=]{
        qDebug() << "后一个按钮被点击";
        if(currentImg<imgCount-1){
            currentImg++;
        }else{
            currentImg = 0;
        }
        setProcessInfo();
        displayImg();
    });

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
    QFileInfoList imgInfoFiles = CommonUtil::getImageFileInfoList(dirPath);
    imgCount =  imgInfoFiles.size();
    qDebug()<<"共找到" << imgCount<<"张图片";
//    设置数据之前,先清空旧数据
    imgFilesItemModel->clear();
//    这里不能设置行数,因为此处如果设置了行数,会与下面appendRow()产生干扰,如实际是1行,先setRowCount(1),然后又appendRow()了一次,那么当以后使用imgFilesItemModel.rowCount()时,将返回2,因此此处不能设置
//    imgFilesItemModel->setRowCount(imgCount);
    for(auto info : imgInfoFiles)
        {
//            定义QStandardItem对象 , 构造方法参数1.行数,2.列数 有默认值
            QStandardItem *imageItem = new QStandardItem(1);
//            为单元项设置属性
//            设置Icon属性
            imageItem->setIcon(QIcon(info.absoluteFilePath()));
//            将文件的路径设置到data中
            imageItem->setData(info.absoluteFilePath());
//            设置tooltip,不能直接使用
//            imageItem->setToolTip(info.absoluteFilePath());
//            设置文字属性 这里不需要展示文字
//            imageItem->setText(info.fileName());

            qDebug() << "设置的Item:"<< imageItem;
            imgFilesItemModel->appendRow(imageItem);
        }

//    设置数据
    ui->file_list_view->setModel(imgFilesItemModel);
//    设置框选矩形框可见
    ui->file_list_view->setSelectionRectVisible(true);
//    设置选择模式，该模式为最常用模式，其他选择模式请自行查看帮助说明
//    按住ctrl可多选，按住shift可连续多选
//    当点击另一个item，其他被选中的item会取消选中状态
//    ui->file_list_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
//    设置QStandardItem中单元项的图片大小
    ui->file_list_view->setIconSize(QSize(90,95));
//    设置QStandardItem中单元项的间距
    ui->file_list_view->setSpacing(10);
//    设置不显示滚动条
    ui->file_list_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->file_list_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    currentImg = 0;
    setProcessInfo();
    displayImg();
}

void MainWidget::setProcessInfo(){
    QString info = QString("已标注%1/ 总%2   当前位置：%3").arg(hasMarkCount).arg(imgCount).arg(currentImg+1);
    ui->progress_info->setText(info);
//    设置进度条最大值
    ui->progress_bar->setMaximum(imgCount);
//    设置进度条当前的运行值
    ui->progress_bar->setValue(hasMarkCount);
}

void MainWidget::displayImg(){
    qDebug() << "主界面展示图片";
    qDebug() <<"imgFilesItemModel 总行数："<<imgFilesItemModel->rowCount();
    QStandardItem *item = imgFilesItemModel->item(currentImg);

    qDebug() << "获取的Item:"<< item;

//    得到存储在item中的data数据
    QVariant variant = item->data();
//    当前图片文件路径
    QString currentFilePath = variant.toString();
    qDebug()<<"当前展示的图片路径是："<<currentFilePath;
    QPixmap pixmap ;
    pixmap.load(currentFilePath);
    QGraphicsScene *scene =new QGraphicsScene(this);


    scene->addPixmap(pixmap);
    ui->main_graphics_view->setScene(scene);
    ui->main_graphics_view->show();
}

void MainWidget::on_settingButton_clicked()
{
}
void MainWidget::on_exportButton_clicked()
{
    ExportDialog *exportDialog = new ExportDialog(this);
//    设置dialog为模态框
    exportDialog->setModal(true);
    exportDialog->exec();
}
void MainWidget::on_moveButton_clicked()
{
}
void MainWidget::on_importButton_clicked()
{
    ImportDialog *importDialog = new ImportDialog(this);
//    设置dialog为模态框
    importDialog->setModal(true);
    importDialog->exec();
}
