#include "maininterface.h"
#include "ui_maininterface.h"



//蒙版全局变量初始化
QWidget *MainInterface::g_masking = NULL;
//引用IndexWidget的全局变量
extern QString CURRENT_PROJECT_FILE_PATH;

MainInterface::MainInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    CommonUtil::setQssStyle(":/res/style/scrollbar_style.qss",this);

//    初始化自定义的UI
    initCustomUI();

//    如果没有得到当前项目的文件路径,就不再进行下去
    if (CURRENT_PROJECT_FILE_PATH.isEmpty()) return;

//    实例化QStandardItemModel
    notReviewImgFilesItemModel = new QStandardItemModel;
    hasReviewImgFilesItemModel = new QStandardItemModel;
    markInfoItemModel = new QStandardItemModel;
    metaMarkInfoItemModel = new QStringListModel;
//    初始化项目信息,包括图片文件夹的路径/标注的预设信息/已经标注过的信息
    initProjectInfo();
//    createDockDockWidget();


    connect(ui->main_graphics_view,&MarkGraphicsView::scaleChange,this,&MainInterface::setSizeProportionText);

}


void MainInterface::initCustomUI()
{
//    设置图标( 窗口图标,(操作系统)状态栏图标)
    qDebug()<<"重新设置窗体标题/图标";
    setWindowIcon(QIcon(":/res/icons/kanyun.png"));
    setWindowTitle("看云图片标注精灵");
//    去掉标题栏
    setWindowFlags(Qt::FramelessWindowHint);

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
//    QMainWindow::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);



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


    QVBoxLayout *menuVerticalLayout = new QVBoxLayout(ui->menu_frame);
    menuVerticalLayout->setSpacing(6);
    menuVerticalLayout->setMargin(0);
    menuVerticalLayout->setContentsMargins(0,0,0,0);

//    该方法并不能让该布局中的组件水平居中,除非该布局中的组件只有一个,否则多个组件会挤在一块,因此如果多个组件需要水平居中,需要在addWidget时进行指定
//    menuVerticalLayout->setAlignment(Qt::AlignHCenter);

//    定义按钮
    MenuButton *fontButton = new MenuButton(":/res/icons/font.png","前一个",false);
    MenuButton *afterButton = new MenuButton(":/res/icons/after.png","后一个",false);
    MenuButton *settingButton = new MenuButton(":/res/icons/setting.png","设置",false);
    MenuButton *moveButton = new MenuButton(":/res/icons/move.png","移动",true);
    MenuButton *rectButton = new MenuButton(":/res/icons/rect.png","矩形框",true);
    MenuButton *importButton = new MenuButton(":/res/icons/import.png","导入",false);
    MenuButton *exportButton = new MenuButton(":/res/icons/export.png","导出",false);

//    分隔线
    QFrame * line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

//    将按钮添加进menu_frame中
    menuVerticalLayout->addWidget(moveButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(line);
    menuVerticalLayout->addWidget(rectButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(fontButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(afterButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(settingButton,0,Qt::AlignHCenter);

    menuVerticalLayout->addWidget(importButton,0,Qt::AlignHCenter);
    menuVerticalLayout->addWidget(exportButton,0,Qt::AlignHCenter);

//   设置按钮对象的名称方便后续可以根据组件名称写槽函数(利用QMetaObject::connectSlotsByName(QObject *o)),而不必每个按钮都去写connect()函数
//   原来想的是通过规范命名,即可不必再写connect()连接函数,结果对于自定义的控件来说,并不能实现,需要注意,因此还需要手动写connect()函数
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
    connect(settingButton,&MenuButton::clicked,this,&MainInterface::on_settingButton_clicked);
    connect(moveButton,&MenuButton::clicked,this,&MainInterface::on_moveButton_clicked);
    connect(importButton,&MenuButton::clicked,this,&MainInterface::on_importButton_clicked);
    connect(exportButton,&MenuButton::clicked,this,&MainInterface::on_exportButton_clicked);


    connect(ui->save_btn,&QPushButton::clicked,this,&MainInterface::on_saveButton_clicked);
    connect(ui->review_btn,&QPushButton::clicked,this,&MainInterface::on_reviewButton_clicked);

    connect(ui->minimize_window_btn,&QPushButton::clicked,this,&MainInterface::on_minimizeWindowButton_clicked);
    connect(ui->custom_window_btn,&QPushButton::clicked,this,&MainInterface::on_customWindowButton_clicked);
    connect(ui->close_window_btn,&QPushButton::clicked,this,&MainInterface::on_closeWindowButton_clicked);

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
    ui->left_file_listView->setFrameShape(QListView::NoFrame);
    ui->right_file_listView->setFrameShape(QListView::NoFrame);
//    左边的listview展现是从右向左
    ui->left_file_listView->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    ui->right_file_listView->setLayoutDirection(Qt::LayoutDirection::LeftToRight);


//    父窗口蒙版
    g_masking = new QWidget(this,Qt::FramelessWindowHint);
    g_masking->resize(maximumSize());
    g_masking->setObjectName("g_masking");
    g_masking->setStyleSheet("#g_masking{background-color:rgb(10,10,10,100)}");
    g_masking->hide();

}

void MainInterface::initProjectInfo()
{

    currentProject = CommonUtil::readProjectInfo(CURRENT_PROJECT_FILE_PATH);
    qDebug() << QString("初始化项目信息：[项目路径：%1 图片文件夹路径：%2]").arg(CURRENT_PROJECT_FILE_PATH).arg(currentProject.imgPath);
//    标注内容预定义信息
    metaMarkInfoList = currentProject.annotationMeta.split(",");
    metaMarkInfoItemModel->setStringList(metaMarkInfoList);
//    图片文件夹路径
    dirPath = currentProject.imgPath;
//    已标注过的信息
    markInfoCollection = currentProject.markCollection;
//    foreach(const QString key,storgeCollection.keys()){
//       markInfoCollection[key] = storgeCollection[key].value<QList<RectMeta>>();
//    }
}

MainInterface::~MainInterface()
{
    delete ui;
}



void MainInterface::loadImage()
{
    if(dirPath.isEmpty()) return;
    QFileInfoList imgInfoFiles = CommonUtil::getImageFileInfoList(dirPath);
    imgCount =  imgInfoFiles.size();
    qDebug()<< "选择的路径是：" << dirPath << "  共找到" << imgCount << "张图片";
    if(imgCount == 0) return;
//    设置数据之前,先清空旧数据
    notReviewImgFilesItemModel->clear();
    hasReviewImgFilesItemModel->clear();
//    这里不能设置行数,因为此处如果设置了行数,会与下面appendRow()产生干扰,如实际是1行,先setRowCount(1),然后又appendRow()了一次,那么当以后使用imgFilesItemModel.rowCount()时,将返回2,因此此处不能设置
//    imgFilesItemModel->setRowCount(imgCount);

    int list_view_height = ui->left_file_listView->height();
    int list_view_width = ui->left_file_listView->width();
    qDebug() << "QListView的高度：" << list_view_height << "  宽度：" << list_view_width;
    for(auto info : imgInfoFiles){
//       定义QStandardItem对象 , 构造方法参数1.行数,2.列数 有默认值
        QStandardItem *imageItem = new QStandardItem(1);
//       为单元项设置属性
//       设置Icon属性
        imageItem->setIcon(QIcon(info.absoluteFilePath()));
//       将文件的路径设置到data中
        imageItem->setData(info.absoluteFilePath());
//       设置tooltip,不能直接使用
//       imageItem->setToolTip(info.absoluteFilePath());
//       设置文字属性 这里不需要展示文字
//       imageItem->setText("占位符不占");
//       设置每个Item的尺寸,这个是体现在QListView中的尺寸(可以通过点击item得到的选中尺寸)
        imageItem->setSizeHint(QSize(list_view_height,list_view_height));
        imageItem->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
//       默认情况下 双击item是可以进行编辑的,这里禁用编辑
        imageItem->setEditable(false);
        imageItem->setCheckable(false);
        qDebug() << "设置的Item:" << imageItem;
//        添加到未查看的model中
        notReviewImgFilesItemModel->appendRow(imageItem);

//       以文件路径为Key,放进总集合中。
        if (!markInfoCollection.contains(info.absoluteFilePath())){
            markInfoCollection[info.absoluteFilePath()];
        }

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
    ui->left_file_listView->setSpacing(0);
    ui->right_file_listView->setSpacing(0);




//    设置QListView中各个item占的图片大小(能压缩但不能拉伸) 最好与QStandardItem::setSizeHint() 配合使用
    ui->left_file_listView->setIconSize(QSize(list_view_height,list_view_height));
    ui->right_file_listView->setIconSize(QSize(list_view_height,list_view_height));

//    不能移动item
    ui->right_file_listView->setMovement(QListView::Static);
    ui->left_file_listView->setMovement(QListView::Static);


//    QListView设置自定义委托
    FileListDelegate *deleteLater = new FileListDelegate();
    ui->right_file_listView->setItemDelegate(deleteLater);
    ui->left_file_listView->setItemDelegate(deleteLater);

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

    ui->right_file_listView->setItemAlignment(Qt::AlignVCenter);
    ui->left_file_listView->setItemAlignment(Qt::AlignCenter|Qt::AlignVCenter);
//    控件不允许拖动
    ui->left_file_listView->setDragEnabled(false);
    ui->right_file_listView->setDragEnabled(false);

    ui->left_file_listView->setResizeMode(QListView::Adjust);
    ui->right_file_listView->setDragEnabled(QListView::Adjust);
//    设置当前图片索引为0
    currentImgIndex = 0;
//    取得当前图片Item
    currentImgItem = notReviewImgFilesItemModel->item(currentImgIndex);
    qDebug() << "获取的Item11:"<< currentImgItem;
//    从未查看Model中弹出当前图片Item,因为该方法体在初始化时只执行一次,因此takeRow()方法的参数恒为0,也就是取出第一个Item
    notReviewImgFilesItemModel->takeRow(currentImgIndex);

}


void MainInterface::displayImg(){
    qDebug() << "主界面展示图片";

    qDebug() << "获取的Item:"<< currentImgItem;

//    得到存储在item中的data数据
    QVariant variant = currentImgItem->data();
//    当前图片文件路径
    QString currentFilePath = variant.toString();
    qDebug()<<"当前展示的图片路径是："<<currentFilePath;

//    设置图元在容器中的展示位置
    ui->main_graphics_view->setAlignment(Qt::AlignCenter);
//    创建场景(自定义的场景类)
    scene = new MarkGraphicsScene(ui->main_graphics_view);
//    scene->addPixmap(pixmap);
//    创建图元(自定义的图元,存放要标注的图片)
    graphicsPixmapItem = new MarkGraphicsPixmapItem(currentFilePath);
//    在场景中,添加要被标注的图元
    scene->addItem(graphicsPixmapItem);
//    自定义视图,设置场景
    ui->main_graphics_view->setScene(scene);
//    调用自定义视图的adapt()方法,用于自适应显示
    ui->main_graphics_view->adapt();
//    ui->main_graphics_view->clearMask();
    ui->main_graphics_view->show();
    setSizeProportionText();

//    槽函数:添加标注信息
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF)>(&MarkGraphicsScene::addMarkItem),this,&MainInterface::addRectMarkInfo);
//    槽函数:删除标注信息
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF)>(&MarkGraphicsScene::deleteMarkItem),this,&MainInterface::removeRectMarkInfo);
//    槽函数：修改标注信息(主要是item的坐标产生变化)
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF,QRectF)>(&MarkGraphicsScene::updateMarkItem),this,&MainInterface::updateRectMarkInfo);
//    槽函数：图片上的item被选中
    connect(scene,static_cast<void (MarkGraphicsScene::*)(QRectF,bool)>(&MarkGraphicsScene::itemSelectState),this,&MainInterface::itemSelectState);


//    清空标注信息的model
    markInfoItemModel->clear();
//    初始化当前图片标注信息
    initMarkInfo();
}

void MainInterface::on_settingButton_clicked()
{
    SettingDialog *settingDialog = new SettingDialog(this);
//    设置dialog为模态框
    settingDialog->setModal(true);
    settingDialog->setImageLocalPath(dirPath);
    settingDialog->setAnnotationMeta(metaMarkInfoList);
    connect(settingDialog,static_cast<void (SettingDialog::*)(QString)>(&SettingDialog::settingChanged),this,&MainInterface::saveSettingChange);
    MainInterface::g_masking->show();
    settingDialog->exec();
    MainInterface::g_masking->hide();
}
void MainInterface::on_exportButton_clicked()
{
    ExportDialog *exportDialog = new ExportDialog(this);
//    设置dialog为模态框
    exportDialog->setModal(true);
    connect(this,static_cast<void (MainInterface::*)(QString,QMap<QString,QList<RectMetaInfo>>)>(&MainInterface::sendExportLocalPathAndCollection),exportDialog,&ExportDialog::setExportLocalPathAndMarkInfoCollection);
    emit sendExportLocalPathAndCollection(dirPath,markInfoCollection);
    MainInterface::g_masking->show();
//    注意connect()函数的位置
    connect(exportDialog,static_cast<void (ExportDialog::*)(QString,export_type)>(&ExportDialog::sendExportPathAndExportId),this,[=](QString exportPath,export_type exportType){
            this->export_dir_path = exportPath;
            this->export_type_enum = exportType;
            qDebug() << "lambda表达式接收到参数：" << exportPath << exportType;
    });

    int result_code = exportDialog->exec();
    MainInterface::g_masking->hide();

//    如果不是点击的确认导出按钮,则返回
    if (result_code != QDialog::Accepted) return;

    ExportMessageBox *ex = new ExportMessageBox(export_dir_path);
    ex->show();

//  实例化工作类
    ExportWorker *worker = new ExportWorker(export_dir_path,export_type_enum,markInfoCollection);
    QThread* thread = new QThread();
//  当线程启动时，执行Worker类的耗时函数exportMarkData()
    connect(thread,&QThread::started,worker,&ExportWorker::exportMarkData);
//    当耗时函数执行完毕，发出complete()信号时，删除worker实例
    connect(worker,&ExportWorker::complete,ex,[=]{
        ex->export_complete();
        delete worker;
    });
//    当worker对象实例销毁时，退出线程
    connect(worker,SIGNAL(destroyed(QObject*)),thread,SLOT(quit()));
//    当线程结束时，销毁线程对象实例
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
//    移动worker对象实例到线程中
    worker->moveToThread(thread);
//    启动线程
    thread->start();


}
void MainInterface::on_moveButton_clicked()
{
    qDebug() << "移动操作";
}
void MainInterface::on_importButton_clicked()
{
    importDialog = new ImportDialog(this);
//    设置dialog为模态框
    importDialog->setModal(true);
//  Qt5信号槽：  https://www.bbsmax.com/A/Gkz1RVnJR6/
    connect(importDialog,static_cast<void (ImportDialog::*)(QString)>(&ImportDialog::sendData),this,&MainInterface::on_import_function);
    MainInterface::g_masking->show();
    importDialog->exec();
    MainInterface::g_masking->hide();
}

void MainInterface::on_import_function(QString path)
{
    qDebug()<< "接收到importDialog窗口返回值："<<path;
//    清空标注信息集合
    markInfoCollection.clear();
//    读取引入的文件,并将文件内容保存按照格式保存到 markInfoCollection 标注信息集合中
//    1.读取文件,获取图片绝对路径作为markInfoCollection的key
//    2.读取文件内容作为对应key的value
//    3.重置显示

    CommonUtil::readJSonValue(markInfoCollection,path);
    if (markInfoCollection.size() == 0){
        qDebug() << "导入JSON发现集合为空,尝试导入XML";
        CommonUtil::readXmlValue(markInfoCollection,path);
    }

    qDebug() << "导入数据完毕,数据量：" << markInfoCollection.size();
    currentImgIndex = 0;
    imgCount = markInfoCollection.keys().size();
    notReviewImgFilesItemModel->clear();
    hasReviewImgFilesItemModel->clear();
    foreach(const QString key, markInfoCollection.keys()){
        QStandardItem *item = new QStandardItem;
        item->setIcon(QIcon(key));
        item->setData(key);
        notReviewImgFilesItemModel->appendRow(item);
    }
    currentImgItem = notReviewImgFilesItemModel->item(currentImgIndex);
    notReviewImgFilesItemModel->takeRow(currentImgIndex);
    setMarkProgressInfo();
    displayImg();

}

void MainInterface::on_narrowButton_clicked()
{
    qDebug()<< "图片缩小...";
    ui->main_graphics_view->narrow();
    setSizeProportionText();
}

void MainInterface::on_enlargeButton_clicked()
{
    qDebug()<< "图片放大.......";
    ui->main_graphics_view->enlarge();
    setSizeProportionText();
}

void MainInterface::on_adaptWindowButton_clicked()
{
    qDebug()<< "图片回归初始展示......";
    ui->main_graphics_view->adapt();
    setSizeProportionText();
}

void MainInterface::on_saveButton_clicked()
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
    qDebug() << "当前图片信息标注信息：" << rectMetas;
    markInfoCollection[currentFilePath] = rectMetas;

    qDebug() << "总集合的数量" << markInfoCollection[currentImgItem->data().toString()].size();
//    设置标注进度信息
    setMarkProgressInfo();
//    保存到项目文件中去
//    QMap<QString,QList<RectMeta>> saveCollection;
//    foreach(const QString key,markInfoCollection.keys()){
//       QVariant v = QVariant::fromValue(markInfoCollection[key]);
//       saveCollection[key] = v;
//    }
    currentProject.markCollection = markInfoCollection;
//    currentProject.lastLabelTime = QString(QDateTime::currentDateTime().toTime_t());
//    CommonUtil::saveProjectInfo(currentProject);
//    弹出吐司
    QToast::ShowText("已保存");
}

void MainInterface::on_reviewButton_clicked()
{
    qDebug()<< "查看按钮被点击......";
    reviewDialog = new ReviewDialog(this);
//    设置dialog为模态框
    reviewDialog->setModal(true);
    reviewDialog->setMarkInfoTable(markInfoCollection);
    connect(this,static_cast<void (MainInterface::*)(QString,QMap<QString,QList<RectMetaInfo>>)>(&MainInterface::sendExportLocalPathAndCollection),reviewDialog,&ReviewDialog::setExportLocalPath);
    emit sendExportLocalPathAndCollection(dirPath,markInfoCollection);
    MainInterface::g_masking->show();
    int return_code = reviewDialog->exec();
    MainInterface::g_masking->hide();
    if (return_code == QDialog::Accepted){
        qDebug() << "说明点击的是导出按钮";
        on_exportButton_clicked();
    }else{
        qDebug() << "说明点击的是Dialog右上角的关闭按钮";
    }


}

void MainInterface::on_closeWindowButton_clicked()
{
   this->close();
}
void MainInterface::on_customWindowButton_clicked()
{
    if(isMaximized()){
//        如果已经是最大化窗口,那么就缩小,否则就设置为最大化窗口
       showNormal();

    }else{
        showMaximized();
    }
}
void MainInterface::on_minimizeWindowButton_clicked()
{
    this->showMinimized();
}

void MainInterface::initMarkInfo()
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
//    自定义委托[传入标注元数据信息]
    AnnotationDelegate *delegate = new AnnotationDelegate(metaMarkInfoList);
//    设置自定义委托信号连接
    connect(delegate,reinterpret_cast<void (AnnotationDelegate::*)(QString,QModelIndex)>(&AnnotationDelegate::markTextInfoUpdate),this,&MainInterface::markInfoTextChange);
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

void MainInterface::configAnnotationDisplay(QStandardItem *item)
{
//          设置每个Item的尺寸,这里控制的是QComboBox的宽度和高度。
          item->setSizeHint(QSize(80,50));
          QModelIndex index = markInfoItemModel->indexFromItem(item);
//          打开持久编辑器
          ui->annotation_list_view->openPersistentEditor(index);
//        设置listview中的控件为QComboBox
          QComboBox *cmb =new QComboBox;
//          设置QComboBox是否可编辑
          cmb->setEditable(false);
          cmb->setModel(metaMarkInfoItemModel);
          cmb->setEditText(item->text());
//          setIndexWidget要生效，必须setModel(model)的后面
//          ui->annotation_list_view->setIndexWidget(index, cmb);

}

void MainInterface::addRectMarkInfo(QRectF rectf)
{
    RectMeta rectMeta;
    rectMeta.x = rectf.x();
    rectMeta.y = rectf.y();
    rectMeta.w = rectf.width();
    rectMeta.h = rectf.height();
//    如果之前没有标记过,则使用下拉框中的第一个文字信息,否则使用上次输入的信息
    if (lastMarkInfo.isEmpty()){
      lastMarkInfo = metaMarkInfoItemModel->stringList().at(0);
      qDebug() << "由于找不到上一次的标注文字信息,因此使用默认文字代替：" << lastMarkInfo;
    }
    rectMeta.text  = lastMarkInfo;
    qDebug() << "接收到一个标注信息：" << rectMeta;

    QStandardItem *item = new QStandardItem;
//    将结构体变成QVariant
    item->setData(QVariant::fromValue(rectMeta));
    item->setText(rectMeta.text);
    markInfoItemModel->appendRow(item);
    configAnnotationDisplay(item);
}

void MainInterface::removeRectMarkInfo(QRectF rectf)
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


void MainInterface::updateRectMarkInfo(QRectF oldRectF,QRectF newRectF)
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




void MainInterface::resizeEvent(QResizeEvent *event){
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    if(isMaximized()){
//        如果窗口已经是最大状态,则设置图片为自定义大小图标
         ui->custom_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarNormalButton));
    }else{
        ui->custom_window_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarMaxButton));
    }
}

void MainInterface::showEvent(QShowEvent *event)
{
    qDebug() << "MainInterface showEvent() 执行,需要注意的是,如果最小化窗口,再显示也会触发该方法";
//   如果没有得到当前项目的文件路径,就不再进行下去
    if (CURRENT_PROJECT_FILE_PATH.isEmpty()) return;
//   如果imgCount不为0,说明是已经初始化过的,将不再进行下面的操作
    if (imgCount != 0) return;
//  下面这些操作,原来是在构造函数中完成的,但是后来发现在构造函数中获取尺寸,跟构造函数完成之后获取的尺寸不一致,因为构造函数有默认尺寸,
//  因此需要在界面展示之后,再进行下面操作但是showEvent方法,是在显示前触发的,因此加上定时器

    QTimer::singleShot(10,this,[=]{

            createProgressWidget();
            createSizeScaleWidget();
//          加载图片
            loadImage();
//          设置标注进度信息
            setMarkProgressInfo();
//          展示图片
            displayImg();
    });

}

void MainInterface::setSizeProportionText()
{
//        得到存储在item中的data数据
        QVariant variant = currentImgItem->data();
//        当前图片文件路径
        QString currentFilePath = variant.toString();
        qDebug() << "当前展示的图片路径是：" << currentFilePath;
        QPixmap srcPixmap(currentFilePath);
        QSize srcSize = srcPixmap.size();
        qDebug() << "原图尺寸：" << srcSize;

        QSize currentSize(ui->main_graphics_view->scene()->width(),ui->main_graphics_view->scene()->height());
        qDebug() << "场景尺寸：" << srcSize;
        qDebug() << "视图尺寸：" << ui->main_graphics_view->size();


//        当前缩放比例
        qreal proportion = ui->main_graphics_view->matrix().m11();
//        得到的比例是qreal类型,先乘以100,再保留两位小数
        sizeScaleWidget->setSizeScale(QString("%1%").arg(QString::number(proportion*100,'f',2)));

}


void  MainInterface::setMarkProgressInfo()
{
    int hasMarkCount = 0;
    foreach(const QString key,markInfoCollection.keys()){
        if(markInfoCollection[key].size() > 0){
            hasMarkCount++;
        }
    }

    QString info = QString("已标注%1/ 总%2   当前位置：%3").arg(hasMarkCount).arg(imgCount).arg(currentImgIndex+1);
    progressWidget->setProgressInfo(info,imgCount,hasMarkCount);
}

void MainInterface::createDockDockWidget()
{
//    定义一个空Widget
    QWidget* emptyTitleBar = new QWidget();
//    定义一个QPalette
    QPalette pal;
    QDockWidget *progressDock = new QDockWidget;

    QWidget* progressDockTitleBar = progressDock->titleBarWidget();
    progressDock->setTitleBarWidget(emptyTitleBar);
//    去掉QDockWidget的标题栏
    delete progressDockTitleBar;

    ProgressWidget *progressWidget = new ProgressWidget();
//    QDockWidget中添加元素
    progressDock->setWidget(progressWidget);
//    设置停靠窗口特性，可移动，可关闭,不可停靠
    progressDock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable | QDockWidget::NoDockWidgetFeatures);
//    设置可停靠区域为主窗口左边和右边
    progressDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea);
    progressDock->setMaximumHeight(100);
//    加这句，下面设置颜色时，可以设置标题和控件主体的颜色，否则只能设置标题栏的颜色
    progressDock->setAutoFillBackground(true);
    progressDock->setPalette(pal);
    pal.setColor(QPalette::Background,Qt::blue);

//    添加DockWidget到界面指定位置,此方法只有QMainWindow及其子类拥有
//    addDockWidget(Qt::LeftDockWidgetArea, progressDock);

}

void MainInterface::createProgressWidget()
{

    progressWidget = new ProgressWidget(ui->file_frame);
    progressWidget->setObjectName("progressWidget");
    progressWidget->show();
}

void MainInterface::createSizeScaleWidget()
{
    sizeScaleWidget = new SizeScaleWidget(ui->file_frame);
    connect(sizeScaleWidget,&SizeScaleWidget::narrow,this,&MainInterface::on_narrowButton_clicked);
    connect(sizeScaleWidget,&SizeScaleWidget::adaptWindow,this,&MainInterface::on_adaptWindowButton_clicked);
    connect(sizeScaleWidget,&SizeScaleWidget::enlarge,this,&MainInterface::on_enlargeButton_clicked);

    sizeScaleWidget->show();
}

void  MainInterface::itemSelectState(QRectF rectf ,bool state)
{
   int rowCout =  markInfoItemModel->rowCount();
   for(int i = 0; i < rowCout ; i++){
       QStandardItem *item = markInfoItemModel->item(i);
       QVariant variant = item->data();
//      将QVariant变成结构体
       RectMeta rectMeta = variant.value<RectMeta>();
       if(rectMeta.w == rectf.width() && rectMeta.h == rectf.height() && rectMeta.x == rectf.x() && rectMeta.y == rectf.y()){
           qDebug() << "Model中找到了对应数据";
           if(state){
//               选中状态

           }else{
//               取消选中状态
           }

//         ui->annotation_list_view.
       }
   }
}

void MainInterface::markInfoTextChange(QString newText, QModelIndex index)
{
   QStandardItem *item =  markInfoItemModel->itemFromIndex(index);
   QVariant va = item->data();
   RectMeta rectMeta = va.value<RectMeta>();
   qDebug() << "接收到标注信息改变信号：标注信息从 " << rectMeta.text << " 变为： " << newText;
   rectMeta.text = newText;
   lastMarkInfo = newText;
}

void MainInterface::saveSettingChange(QString annotationMetaInfo)
{
   metaMarkInfoList =  annotationMetaInfo.split(",");
   metaMarkInfoItemModel->setStringList(metaMarkInfoList);
   currentProject.annotationMeta = annotationMetaInfo;
   CommonUtil::saveProjectInfo(currentProject);
}
