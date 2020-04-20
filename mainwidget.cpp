#pragma execution_character_set("utf-8")
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
#include <QComboBox>
#include <QStyle>

#include <common/commonutil.h>
#include <common/fontawesomeicons.h>

#include <module/exportdialog.h>
#include <module/importdialog.h>
#include <module/settingdialog.h>

#include <custom/annotationdelegate.h>
#include <custom/markgraphicspixmapitem.h>
#include <custom/meta.h>


//蒙版全局变量初始化
QWidget *MainWidget::g_masking = NULL;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    initCustomUI();

//    实例化QStandardItemModel
    notReviewImgFilesItemModel = new QStandardItemModel;
    hasReviewImgFilesItemModel = new QStandardItemModel;
    markInfoItemModel = new QStandardItemModel;
    metaMarkInfoItemModel = new QStringListModel;
    metaMarkInfoList<<"虫"<<"鱼"<<"鸟";
    metaMarkInfoItemModel->setStringList(metaMarkInfoList);



    connect(ui->main_graphics_view,&MarkGraphicsView::scaleChange,this,&MainWidget::setSizeProportionText);

}


void MainWidget::initCustomUI()
{
//    设置图标( 窗口图标,(操作系统)状态栏图标)
    qDebug()<<"重新设置窗体标题/图标";
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
//    QList<QScreen *> screens = QGuiApplication::screens();
//    QScreen* screen = screens.first();
//    QSize size = screen->size();

    qDebug()<<"重新设置窗体大小";

//    最大化显示函数(相当于点了最大化按钮,单独设置这个可能不会生效,参考：https://blog.csdn.net/KayChanGEEK/article/details/77923848)
    showMaximized();
//    辅助窗口最大化的同时,也去掉窗口外边框
    QWidget::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);



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
    CommonUtil::setQssStyle(QString(":/res/style/head_frame_style.qss"),ui->head_frame);
    CommonUtil::setQssStyle(QString(":/res/style/main_frame_style.qss"),ui->main_frame);

    CommonUtil::setQssStyle(QString(":/res/style/progressbar_style.qss"),ui->progress_bar);
//    进度条文本颜色
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::green);
    ui->progress_bar->setPalette(palette);

    QVBoxLayout *menuVerticalLayout = new QVBoxLayout(ui->menu_frame);
    menuVerticalLayout->setSpacing(6);
    menuVerticalLayout->setMargin(0);
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

//    标题栏组件居右
    ui->head_frame->layout()->setAlignment(Qt::AlignRight);

//    得到FontAwesome字体
    QFont font = FontAwesomeIcons::Instance().getFont();

//    放大/缩小/全屏按钮
    ui->narrow_btn->setFlat(true);
    ui->adapt_window_btn->setFlat(true);
    ui->enlarge_btn->setFlat(true);
    ui->adapt_window_btn->setFont(font);
    ui->narrow_btn->setFont(font);
    ui->enlarge_btn->setFont(font);
    ui->adapt_window_btn->setText(FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_fullscreen));
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

//    关闭/最小化/自定义窗口尺寸 按钮
    ui->minimize_window_btn->setFlat(true);
    ui->close_window_btn->setFlat(true);
    ui->custom_window_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->close_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->custom_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarNormalButton));
    ui->minimize_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarMinButton));


    qDebug()<< ui->menu_frame->width()<<ui->file_frame->height();

//    定义连接函数
    connect(openDirButton,&MenuButton::clicked,this,&MainWidget::on_openDirButton_clicked);
    connect(settingButton,&MenuButton::clicked,this,&MainWidget::on_settingButton_clicked);
    connect(moveButton,&MenuButton::clicked,this,&MainWidget::on_moveButton_clicked);
    connect(importButton,&MenuButton::clicked,this,&MainWidget::on_importButton_clicked);
    connect(exportButton,&MenuButton::clicked,this,&MainWidget::on_exportButton_clicked);

    connect(ui->narrow_btn,&QPushButton::clicked,this,&MainWidget::on_narrowButton_clicked);
    connect(ui->enlarge_btn,&QPushButton::clicked,this,&MainWidget::on_enlargeButton_clicked);
    connect(ui->adapt_window_btn,&QPushButton::clicked,this,&MainWidget::on_adaptWindowButton_clicked);

    connect(ui->save_btn,&QPushButton::clicked,this,&MainWidget::on_saveButton_clicked);
    connect(ui->review_btn,&QPushButton::clicked,this,&MainWidget::on_reviewButton_clicked);

    connect(ui->minimize_window_btn,&QPushButton::clicked,this,&MainWidget::on_minimizeWindowButton_clicked);
    connect(ui->custom_window_btn,&QPushButton::clicked,this,&MainWidget::on_customWindowButton_clicked);
    connect(ui->close_window_btn,&QPushButton::clicked,this,&MainWidget::on_closeWindowButton_clicked);

//    下面两个连接函数使用了lambda表达式
    connect(fontButton,&MenuButton::clicked,this,[=]{
        qDebug() << "前一个按钮被点击";
        if(imgCount == 0) return ;
        if(currentImgIndex > 0){
            notReviewImgFilesItemModel->insertRow(0,currentImgItem);
            currentImgItem = hasReviewImgFilesItemModel->item(0);
            hasReviewImgFilesItemModel->takeRow(0);
            currentImgIndex--;
        }else{
//            currentImg = imgCount-1;
             return ;
        }
        setMarkProgressInfo();
        displayImg();
    });
    connect(afterButton,&MenuButton::clicked,this,[=]{
        qDebug() << "后一个按钮被点击";
        if(imgCount == 0) return ;
        if(currentImgIndex<imgCount-1){
//            hasReviewImgFilesItemModel之所以使用insert是因为,hasReviewImgFilesItemModel是从右向左展示顺序,因此倒排,最远的靠近中央
            hasReviewImgFilesItemModel->insertRow(0,currentImgItem);
            currentImgItem = notReviewImgFilesItemModel->item(0);
            notReviewImgFilesItemModel->takeRow(0);
            currentImgIndex++;
        }else{
//            currentImg = 0;
            return ;
        }
        setMarkProgressInfo();
        displayImg();
    });

    ui->head_frame->setFrameShape(QListView::NoFrame);
//    去掉listview边框
//    ui->left_file_listView->setFrameShape(QListView::NoFrame);
//    ui->right_file_listView->setFrameShape(QListView::NoFrame);
//    左边的listview展现是从右向左
    ui->left_file_listView->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    ui->right_file_listView->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

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
    dirPath = QFileDialog::getExistingDirectory(this, QString("选择文件夹"),
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

//    设置框选矩形框可见性
    ui->left_file_listView->setSelectionRectVisible(false);
    ui->right_file_listView->setSelectionRectVisible(false);
//    设置选择模式，该模式为最常用模式，其他选择模式请自行查看帮助说明
//    按住ctrl可多选，按住shift可连续多选
//    当点击另一个item，其他被选中的item会取消选中状态
//    ui->file_list_view->setSelectionMode(QAbstractItemView::ExtendedSelection);

//   设置ListViw中单元项的间距(但是发现在ListView中setSpacing()不仅影响了控件间的距离还影响了控件与其父容器之间的距离,因此改用qss处理)
//    ui->left_file_listView->setSpacing(6);
//    ui->right_file_listView->setSpacing(6);

    int h = ui->left_file_listView->height();
    int w = ui->left_file_listView->width();
    qDebug() << "QListView的高度："<< h << "  宽度："<<w;
    QSize size(h-23,h-23);
//    设置QStandardItem中单元项的图片大小
    ui->left_file_listView->setIconSize(size);
    ui->right_file_listView->setIconSize(size);

//    设置显示模式为IconModel
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
//    控件不允许拖动
    ui->left_file_listView->setDragEnabled(false);
    ui->right_file_listView->setDragEnabled(false);

    currentImgIndex = 0;
    currentImgItem = notReviewImgFilesItemModel->item(currentImgIndex);
    notReviewImgFilesItemModel->takeRow(currentImgIndex);
    setMarkProgressInfo();
    displayImg();
}


void MainWidget::displayImg(){
    qDebug() << "主界面展示图片";

    qDebug() << "获取的Item:"<< currentImgItem;

//    得到存储在item中的data数据
    QVariant variant = currentImgItem->data();
//    当前图片文件路径
    QString currentFilePath = variant.toString();
    qDebug()<<"当前展示的图片路径是："<<currentFilePath;

//    设置图元在容器中的展示位置
    ui->main_graphics_view->setAlignment(Qt::AlignCenter);

    scene =new MarkGraphicsScene(ui->main_graphics_view);
//    scene->addPixmap(pixmap);
    graphicsPixmapItem = new MarkGraphicsPixmapItem(currentFilePath);

    scene->addItem(graphicsPixmapItem);
    ui->main_graphics_view->setScene(scene);
    ui->main_graphics_view->adapt();
//    ui->main_graphics_view->clearMask();
    ui->main_graphics_view->show();
    setSizeProportionText();

//    槽函数:添加标注信息
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF)>(&MarkGraphicsScene::addMarkItem),this,&MainWidget::addRectMarkInfo);
//    槽函数:删除标注信息
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF)>(&MarkGraphicsScene::deleteMarkItem),this,&MainWidget::removeRectMarkInfo);
//    槽函数：修改标注信息(主要是item的坐标产生变化)
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF,QRectF)>(&MarkGraphicsScene::updateMarkItem),this,&MainWidget::updateRectMarkInfo);


//    清空标注信息的model
    markInfoItemModel->clear();
//    初始化当前图片标注信息
    initMarkInfo();
}

void MainWidget::on_settingButton_clicked()
{
    SettingDialog *settingDialog = new SettingDialog(this);
//    设置dialog为模态框
    settingDialog->setModal(true);
    connect(this,static_cast<void (MainWidget::*)(QString)>(&MainWidget::sendImageLocalPath),settingDialog,&SettingDialog::setImageLocalPath);
    emit sendImageLocalPath(dirPath);
    MainWidget::g_masking->show();
    settingDialog->exec();
    MainWidget::g_masking->hide();
}
void MainWidget::on_exportButton_clicked()
{
    ExportDialog *exportDialog = new ExportDialog(this);
//    设置dialog为模态框
    exportDialog->setModal(true);
    connect(this,static_cast<void (MainWidget::*)(QString)>(&MainWidget::sendExportLocalPath),exportDialog,&ExportDialog::setExportLocalPath);
    emit sendExportLocalPath(dirPath);
    MainWidget::g_masking->show();
    exportDialog->exec();
    MainWidget::g_masking->hide();
}
void MainWidget::on_moveButton_clicked()
{
    qDebug() << "移动操作";
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
//    清空标注信息集合
    markInfoCollection.clear();
//    读取引入的文件,并将文件内容保存按照格式保存到 markInfoCollection 标注信息集合中
//    1.读取文件,获取图片绝对路径作为markInfoCollection的key
//    2.读取文件内容作为对应key的value
}

void MainWidget::on_narrowButton_clicked()
{
    qDebug()<< "图片缩小...";
    ui->main_graphics_view->narrow();
    setSizeProportionText();
}

void MainWidget::on_enlargeButton_clicked()
{
    qDebug()<< "图片放大.......";
    ui->main_graphics_view->enlarge();
    setSizeProportionText();
}

void MainWidget::on_adaptWindowButton_clicked()
{
    qDebug()<< "图片回归初始展示......";
    ui->main_graphics_view->adapt();
    setSizeProportionText();
}

void MainWidget::on_saveButton_clicked()
{
    qDebug()<< "保存按钮被点击......";
    if (markInfoCollection.keys().size() == 0) return ;
    QString currentFilePath =  currentImgItem->data().toString();

    if(!markInfoCollection.contains(currentFilePath)){
        markInfoCollection[currentFilePath].clear();
    }

    QList<RectMeta> rectMetas;
    int rowCount = markInfoItemModel->rowCount();
    for(int i = 0;i<rowCount;i++){
        QStandardItem *item =  markInfoItemModel->item(i);
        QVariant variant = item->data();
//      将QVariant变成结构体
        RectMeta rectMeta = variant.value<RectMeta>();
        rectMetas << rectMeta;
    }

    markInfoCollection[currentFilePath] = rectMetas;

    qDebug() << "总集合的数量" << markInfoCollection[currentImgItem->data().toString()].size();
    setMarkProgressInfo();
    QToast::ShowText("已保存");
}

void MainWidget::on_reviewButton_clicked()
{
    qDebug()<< "查看按钮被点击......";
}

void MainWidget::on_closeWindowButton_clicked()
{
   this->close();
}
void MainWidget::on_customWindowButton_clicked()
{
    if(isMaximized()){
//        如果已经是最大化窗口,那么就缩小,否则就设置为最大化窗口
       showNormal();

    }else{
        showMaximized();
    }
}
void MainWidget::on_minimizeWindowButton_clicked()
{
    this->showMinimized();
}

void MainWidget::initMarkInfo()
{
//    从标注集合中获取当前图片的标注集合,然后放到model中
    QList<RectMeta> rectMetas =  markInfoCollection[currentImgItem->data().toString()];
    for(RectMeta rectMeta : rectMetas){

        scene->addItemFromStorage(QRectF(rectMeta.x,rectMeta.y,rectMeta.w,rectMeta.h));

        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(rectMeta));
        item->setText(rectMeta.text);
        markInfoItemModel->appendRow(item);
    }
    AnnotationDelegate *delegate = new AnnotationDelegate;
    ui->annotation_list_view->setModel(markInfoItemModel);
//    设置委托(MVVM视图到模型)
    ui->annotation_list_view->setItemDelegate(delegate);
//    QListView默认是可以编辑的，可以用setEditTrigers设置QListView的条目是否可以编辑，以及如何进入编辑状态，比如表示在双击，或者选择并单击列表项目,也可以设置不可编辑QAbstractItemView::NoEditTriggers
    ui->annotation_list_view->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->annotation_list_view->setSpacing(5);
    ui->annotation_list_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int rowCount = markInfoItemModel->rowCount();
    for(int i = 0; i < rowCount; i++) {
          QStandardItem *item =  markInfoItemModel->item(i);
          configAnnotationDisplay(item);
      }


}

void MainWidget::configAnnotationDisplay(QStandardItem *item)
{
//          设置每个Item的尺寸,这里控制的是QComboBox的宽度和高度。
          item->setSizeHint(QSize(80,50));
          QModelIndex index = markInfoItemModel->indexFromItem(item);
//        设置listview中的控件为QComboBox
          QComboBox *cmb =new QComboBox;
//          设置QComboBox是否可编辑
          cmb->setEditable(true);
          cmb->setModel(metaMarkInfoItemModel);
          cmb->setEditText(item->text());
//          setIndexWidget要生效，必须setModel(model)的后面
          ui->annotation_list_view->setIndexWidget(index, cmb);

}

void MainWidget::addRectMarkInfo(QRectF rectf)
{
    RectMeta rectMeta;
    rectMeta.x = rectf.x();
    rectMeta.y = rectf.y();
    rectMeta.w = rectf.width();
    rectMeta.h = rectf.height();
    rectMeta.text  = "看云22";
    qDebug() << "接收到一个标注信息：" << rectMeta;

    QStandardItem *item = new QStandardItem;
//    将结构体变成QVariant
    item->setData(QVariant::fromValue(rectMeta));
    item->setText(rectMeta.text);
    markInfoItemModel->appendRow(item);
    configAnnotationDisplay(item);
}

void MainWidget::removeRectMarkInfo(QRectF rectf)
{
   qDebug() << "删除标注信息";

   int rowCount = markInfoItemModel->rowCount();
   for(int i = 0; i < rowCount; i++){
       QStandardItem *item =  markInfoItemModel->item(i);
       QVariant variant = item->data();
//     将QVariant变成结构体
       RectMeta rectMeta = variant.value<RectMeta>();
       if(rectMeta.w == rectf.width() && rectMeta.h == rectf.height() && rectMeta.x == rectf.x() && rectMeta.y == rectf.y()){
           qDebug() << "Model中找到了对应数据";
           markInfoItemModel->removeRow(i);
           break;
       }
   }

}


void MainWidget::updateRectMarkInfo(QRectF oldRectF,QRectF newRectF)
{
    qDebug() << "修改标注信息";
    int rowCount = markInfoItemModel->rowCount();
    for(int i = 0;i<rowCount;i++){
        QStandardItem *item =  markInfoItemModel->item(i);
        QVariant variant = item->data();
//      将QVariant变成结构体
        RectMeta rectMeta = variant.value<RectMeta>();
        if(rectMeta.w == oldRectF.width() && rectMeta.h == oldRectF.height() && rectMeta.x == oldRectF.x() && rectMeta.y == oldRectF.y()){
            qDebug() << "Model中找到了对应数据";
            rectMeta.x=newRectF.x();
            rectMeta.y=newRectF.y();
            break;
        }
    }
}




void MainWidget::resizeEvent(QResizeEvent *event){
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    if(isMaximized()){
         ui->custom_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarNormalButton));
    }else{
        ui->custom_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarMaxButton));
    }
}

void MainWidget::setSizeProportionText()
{
//        得到存储在item中的data数据
        QVariant variant = currentImgItem->data();
//        当前图片文件路径
        QString currentFilePath = variant.toString();
        qDebug()<<"当前展示的图片路径是："<<currentFilePath;
        QPixmap srcPixmap(currentFilePath);
        QSize srcSize = srcPixmap.size();
        qDebug() << "原图尺寸："<< srcSize;

        QSize currentSize(ui->main_graphics_view->scene()->width(),ui->main_graphics_view->scene()->height());
        qDebug() << "场景尺寸："<< srcSize;
        qDebug() << "视图尺寸："<< ui->main_graphics_view->size();


//        当前缩放比例
        qreal proportion = ui->main_graphics_view->matrix().m11();
//        得到的比例是qreal类型,先乘以100,再保留两位小数
        ui->scale->setText(QString("%1%").arg(QString::number(proportion*100,'f',2)));

}


void  MainWidget::setMarkProgressInfo()
{
    int hasMarkCount = 0;
    foreach(const QString key,markInfoCollection.keys()){
        if(markInfoCollection[key].size() > 0){
            hasMarkCount++;
        }
    }

    QString info = QString("已标注%1/ 总%2   当前位置：%3").arg(hasMarkCount).arg(imgCount).arg(currentImgIndex+1);
    ui->progress_info->setText(info);
//    设置进度条最大值
    ui->progress_bar->setMaximum(imgCount);
//    设置进度条当前的运行值
    ui->progress_bar->setValue(hasMarkCount);
}
