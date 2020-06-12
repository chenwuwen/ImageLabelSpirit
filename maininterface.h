#pragma execution_character_set("utf-8")
#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QGraphicsScene>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QWidget>
#include <QClipboard>
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
#include <QThread>
#include <QDateTime>
#include <QShowEvent>
#include <QMainWindow>
#include <QApplication>
#include <QDockWidget>



#include <common/commonutil.h>
#include <common/fontawesomeicons.h>
#include <common/exportworker.h>

#include <module/exportdialog.h>
#include <module/importdialog.h>
#include <module/settingdialog.h>
#include <module/reviewdialog.h>
#include <module/exportmessagebox.h>
#include <module/progresswidget.h>
#include <module/sizescalewidget.h>
#include <widgets/qtoast.h>
#include <widgets/menubutton.h>


#include <custom/annotationdelegate.h>
#include <custom/filelistdelegate.h>
#include <custom/markgraphicspixmapitem.h>
#include <custom/meta.h>
#include <custom/markgraphicspixmapitem.h>
#include <custom/markgraphicsscene.h>


namespace Ui {
class MainInterface;
}

class MainInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();
//    全局变量,即dialog弹出时父窗口蒙版指针
    static QWidget *g_masking ;
//    在主界面展示图片
    void displayImg();
//    初始化界面内容
    void initCustomUI();
//    加载项目信息
    void loadProjectInfo();
//    从本地磁盘系统加载图片
    void loadImage();
//    加载标注信息列表(一个是在底图上画框,一个是初始化标注信息[展示列表])
    void loadMarkInfo();
//    配置标注信息展示
    void configAnnotationDisplay(QStandardItem *);
//    设置标注进度文字信息
    void setMarkProgressInfo();
    void createDockDockWidget();
//    创建进度区域widget
    void createProgressWidget();
//    创建尺寸区域widget
    void createSizeScaleWidget();

public slots:
//    设置缩放比例的文字信息
    void setSizeProportionText();


private slots:
//    导入按钮点击
    void on_importButton_clicked();
//    设置按钮点击
    void on_settingButton_clicked();
//    导出按钮点击
    void on_exportButton_clicked();
//    移动按钮点击
    void on_moveButton_clicked();
//    缩小按钮被按下
    void on_narrowButton_clicked();
//    放大按钮被按下
    void on_enlargeButton_clicked();
//    适配按钮被按下
    void on_adaptWindowButton_clicked();
//    查看按钮被按下
    void on_reviewButton_clicked();
//    点击保存按钮时,才会保存到总集合中(markInfoCollection),也就是其他操作都时保存在model中,也就是说任何修改操作都需要点击保存按钮,否则仅在数据仅在当前有效,之后无效.
    void on_saveButton_clicked();
//    状态栏最小化按钮被点击
    void on_minimizeWindowButton_clicked();
//    状态栏自定义窗口/最大化窗口按钮被点击
    void on_customWindowButton_clicked();
//    状态栏关闭窗口按钮被点击
    void on_closeWindowButton_clicked();
//    引入标注信息
    void on_import_function(QString);
//    新的标注
    void addRectMarkInfo(QRectF);
//    移除标注
    void removeRectMarkInfo(QRectF);
//    修改标注(标注位置信息发生变化)
    void updateRectMarkInfo(QRectF oldRectF,QRectF newRectF);
//    item被选中
    void itemSelectState(QRectF,bool);
//    标注的文件信息被更改
    void markInfoTextChange(QString newText,QModelIndex index);
//    保存设置改变槽函数
    void saveSettingChange(QString annotationMetaInfo);

signals:
//    自定义信号,发送图片路径和标注信息集合给导出窗口
    void sendExportLocalPathAndCollection(QString,QMap<QString,QList<RectMetaInfo>>);
//    自定义信号,发送图片路径
    void sendImageLocalPath(QString);

protected:
//	窗口改变监听器
    void resizeEvent(QResizeEvent *event) ;
//    窗口显示监听器
    void showEvent(QShowEvent *event);



private:
    Ui::MainInterface *ui;
//   尚未浏览的图片 model对象
    QStandardItemModel *notReviewImgFilesItemModel;
//    已经浏览的图片 model对象
    QStandardItemModel *hasReviewImgFilesItemModel;
//    标注信息 model对象
    QStandardItemModel *markInfoItemModel;
//    标注信息 元数据 model对象(即:预定义的标注信息,即下拉框中的选项)
    QStringListModel *metaMarkInfoItemModel;
    QStringList metaMarkInfoList;
//    当前的Item指针对象
    QStandardItem *currentImgItem;
//    自定义场景类
    MarkGraphicsScene *scene;
//    自定义图片QGraphicsPixmapItem
    MarkGraphicsPixmapItem *graphicsPixmapItem;
//    图片总数
    int imgCount = 0;
//    当前图片索引位置,从0开始
    int currentImgIndex;
//    图片所在目录
    QString dirPath;
//    引入窗口
    ImportDialog *importDialog;
//    查看窗口
    ReviewDialog *reviewDialog;
    ProgressWidget *progressWidget;
    SizeScaleWidget *sizeScaleWidget;
//    标注信息集合,key为图片名称,value为自定义的结构体
    QMap<QString,QList<RectMeta>> markInfoCollection;
//    上次标注的内容
    QString lastMarkInfo;
//    剪切板
    QClipboard *clipboard = QApplication::clipboard();
//    文件导出路径
    QString export_dir_path;
//    导出类型枚举
    export_type export_type_enum;
//    当前项目
    Project currentProject ;
};

#endif // MAININTERFACE_H
