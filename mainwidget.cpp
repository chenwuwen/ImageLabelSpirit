
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
#include <QButtonGroup>

#include <common/commonutil.h>
#include <common/fontawesomeicons.h>

#include <module/exportdialog.h>
#include <module/importdialog.h>


//蒙版全局变量初始化
QWidget *MainWidget::g_masking = NULL;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    initContent();


}


void MainWidget::initContent()
{
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

//    最大化显示函数(相当于点了最大化按钮,单独设置这个可能不会生效,参考：https://blog.csdn.net/KayChanGEEK/article/details/77923848)
    showMaximized();
    QWidget::setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

//    实例化QStandardItemModel
    notReviewImgFilesItemModel = new QStandardItemModel;
    hasReviewImgFilesItemModel = new QStandardItemModel;

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

    QVBoxLayout *menuVerticalLayout = new QVBoxLayout(ui->menu_frame);
    menuVerticalLayout->setSpacing(6);
    menuVerticalLayout->setContentsMargins(0,0,0,0);

//    该方法并不能让该布局中的组件水平居中,除非该布局中的组件只有一个,否则多个组件会挤在一块,因此如果多个组件需要水平居中,需要在addWidget时进行指定
//    menuVerticalLayout->setAlignment(Qt::AlignHCenter);

//    定义按钮
    MenuButton *openDirButton = new MenuButton(":/res/icons/open.png","新建",false);
    MenuButton *fontButton = new MenuButton(":/res/icons/font.png","前一个",false);
    MenuButton *afterButton = new MenuButton(":/res/icons/after.png","后一个",false);
    MenuButton *settingButton = new MenuButton(":/res/icons/setting.png","设置",false);
    MenuButton *moveButton = new MenuButton(":/res/icons/move.png","移动",true);
    MenuButton *rectButton = new MenuButton(":/res/icons/rect.png","矩形框",true);
    MenuButton *importButton = new MenuButton(":/res/icons/import.png","导入",false);
    MenuButton *exportButton = new MenuButton(":/res/icons/export.png","导出",false);
    openDirButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    分隔线
    QFrame * line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

//    将按钮添加进menu_frame中
    menuVerticalLayout->addWidget(moveButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(line);
    menuVerticalLayout->addWidget(rectButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(openDirButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(fontButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(afterButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(settingButton,0,Qt::AlignHCenter);

    menuVerticalLayout->addWidget(importButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(exportButton,0,Qt::AlignHCenter);

//   设置按钮对象的名称方便后续可以根据组件名称写槽函数(利用QMetaObject::connectSlotsByName(QObject *o)),而不必每个按钮都去写connect()函数
//   原来想的是通过规范命名,即可不必再写connect()连接函数,结果对于自定义的控件来说,并不能实现,需要注意,因此还需要手动写connect()函数
    openDirButton->setObjectName(QString::fromUtf8("openDirButton"));
    fontButton->setObjectName(QString::fromUtf8("fontButton"));
    afterButton->setObjectName(QString::fromUtf8("afterButton"));
    settingButton->setObjectName(QString::fromUtf8("settingButton"));
    moveButton->setObjectName(QString::fromUtf8("moveButton"));
    importButton->setObjectName(QString::fromUtf8("importButton"));
    exportButton->setObjectName(QString::fromUtf8("exportButton"));

//    设置该按钮为默认选中状态
    rectButton->setChecked(true);

//    添加按钮组,加入按钮实现按钮互斥
    QButtonGroup *menuButtonGroup = new QButtonGroup(ui->menu_frame);
    menuButtonGroup->addButton(moveButton);
    menuButtonGroup->addButton(rectButton);
//    设置按钮互斥
    menuButtonGroup->setExclusive(true);

//    得到FontAwesome字体
    QFont font = FontAwesomeIcons::Instance().getFont();

//    放大/缩小/全屏按钮
    ui->narrow_btn->setFlat(true);
    ui->full_screen_btn->setFlat(true);
    ui->enlarge_btn->setFlat(true);
    ui->full_screen_btn->setFont(font);
    ui->narrow_btn->setFont(font);
    ui->enlarge_btn->setFont(font);
    ui->full_screen_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_fullscreen));
    ui->narrow_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_search_minus));
    ui->enlarge_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_search_plus));

//    保存/查看 按钮
    ui->review_btn->setFlat(true);
    ui->save_btn->setFlat(true);
//    font.setPointSize(25);
    ui->review_btn->setFont(font);
    ui->save_btn->setFont(font);
    ui->review_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_bars));
    ui->save_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_check));


    qDebug()<< ui->menu_frame->width()<<ui->file_frame->height();

//    定义连接函数
    connect(openDirButton,&MenuButton::clicked,this,&MainWidget::on_openDirButton_clicked);
    connect(settingButton,&MenuButton::clicked,this,&MainWidget::on_settingButton_clicked);
    connect(moveButton,&MenuButton::clicked,this,&MainWidget::on_moveButton_clicked);
    connect(importButton,&MenuButton::clicked,this,&MainWidget::on_importButton_clicked);
    connect(exportButton,&MenuButton::clicked,this,&MainWidget::on_exportButton_clicked);

    connect(ui->narrow_btn,&QPushButton::clicked,this,&MainWidget::on_narrowButton_clicked);
    connect(ui->enlarge_btn,&QPushButton::clicked,this,&MainWidget::on_enlargeButton_clicked);
    connect(ui->full_screen_btn,&QPushButton::clicked,this,&MainWidget::on_fullScreenButton_clicked);

    connect(ui->save_btn,&QPushButton::clicked,this,&MainWidget::on_saveButton_clicked);
    connect(ui->review_btn,&QPushButton::clicked,this,&MainWidget::on_reviewButton_clicked);
//    下面两个连接函数使用了lambda表达式
    connect(fontButton,&MenuButton::clicked,this,[=]{
        qDebug() << "前一个按钮被点击";
        if(imgCount==0) return ;
        if(currentImg>0){
//            hasReviewImgFilesItemModel->takeItem()
            notReviewImgFilesItemModel->insertRow(0,currentItem);
            currentItem = hasReviewImgFilesItemModel->item(currentImg-1);
            hasReviewImgFilesItemModel->takeRow(currentImg-1);
            currentImg--;
        }else{
            currentImg = imgCount-1;
        }
        setProcessInfo();
        displayImg();
    });
    connect(afterButton,&MenuButton::clicked,this,[=]{
        qDebug() << "后一个按钮被点击";
        if(imgCount==0) return ;
        if(currentImg<imgCount-1){
//            hasReviewImgFilesItemModel之所以使用append是因为,hasReviewImgFilesItemModel是从右向左展示顺序
            hasReviewImgFilesItemModel->appendRow(currentItem);
            currentItem = notReviewImgFilesItemModel->item(0);
            notReviewImgFilesItemModel->takeRow(0);

            currentImg++;
        }else{
            currentImg = 0;
        }
        setProcessInfo();
        displayImg();
    });

//    去掉listview边框
//    ui->left_file_listView->setFrameShape(QListView::NoFrame);
//    ui->right_file_listView->setFrameShape(QListView::NoFrame);

//      设置不显示进度条文字
    ui->progress_bar->setTextVisible(false);
//    设置进度条高度
    ui->progress_bar->setFixedHeight(2);

//    父窗口蒙版
    g_masking=new QWidget(this,Qt::FramelessWindowHint);
    g_masking->resize(maximumSize());
    g_masking->setObjectName("g_masking");
    g_masking->setStyleSheet("#g_masking{background-color:rgb(10,10,10,100)}");
    g_masking->hide();

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
    if(dirPath.isEmpty()) return;
    QFileInfoList imgInfoFiles = CommonUtil::getImageFileInfoList(dirPath);
    imgCount =  imgInfoFiles.size();
    qDebug()<<"选择的路径是："<<dirPath <<"  共找到" << imgCount<<"张图片";
    if(imgCount == 0) return;
//    设置数据之前,先清空旧数据
    notReviewImgFilesItemModel->clear();
    hasReviewImgFilesItemModel->clear();
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

            notReviewImgFilesItemModel->appendRow(imageItem);

        }

//    设置数据
    ui->left_file_listView->setModel(hasReviewImgFilesItemModel);
    ui->right_file_listView->setModel(notReviewImgFilesItemModel);
//    设置框选矩形框可见
    ui->left_file_listView->setSelectionRectVisible(true);
//    设置选择模式，该模式为最常用模式，其他选择模式请自行查看帮助说明
//    按住ctrl可多选，按住shift可连续多选
//    当点击另一个item，其他被选中的item会取消选中状态
//    ui->file_list_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
//    设置QStandardItem中单元项的图片大小
    ui->left_file_listView->setIconSize(QSize(90,95));
    ui->right_file_listView->setIconSize(QSize(90,95));
//    设置QStandardItem中单元项的间距
    ui->left_file_listView->setSpacing(10);
    ui->right_file_listView->setSpacing(10);
    ui->left_file_listView->setViewMode(QListView::IconMode);
    ui->right_file_listView->setViewMode(QListView::IconMode);
//    设置不显示滚动条
    ui->left_file_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->left_file_listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->right_file_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->right_file_listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    设置listview展示方向
    ui->left_file_listView->setFlow(QListView::LeftToRight);
    ui->right_file_listView->setFlow(QListView::LeftToRight);
    currentImg = 0;
    currentItem = notReviewImgFilesItemModel->item(currentImg);
    notReviewImgFilesItemModel->takeRow(currentImg);
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

    qDebug() << "获取的Item:"<< currentItem;

//    得到存储在item中的data数据
    QVariant variant = currentItem->data();
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
    importDialog = new ImportDialog(this);
//    设置dialog为模态框
    importDialog->setModal(true);
//  Qt5信号槽：  https://www.bbsmax.com/A/Gkz1RVnJR6/
    connect(importDialog,static_cast<void (ImportDialog::*)(QString)>(&ImportDialog::sendData),this,&MainWidget::on_import_function);
    MainWidget::g_masking->show();
    importDialog->exec();
    MainWidget::g_masking->hide();
}

void MainWidget::on_import_function(QString path)
{
    qDebug()<< "接收到importDialog窗口返回值："<<path;
}

void MainWidget::on_narrowButton_clicked()
{
    qDebug()<< "图片缩小...";
}

void MainWidget::on_enlargeButton_clicked()
{
    qDebug()<< "图片放大.......";
}

void MainWidget::on_fullScreenButton_clicked()
{
    qDebug()<< "图片全屏......";
}

void MainWidget::on_saveButton_clicked()
{
    qDebug()<< "保存按钮被点击......";
}

void MainWidget::on_reviewButton_clicked()
{
    qDebug()<< "查看按钮被点击......";
}
