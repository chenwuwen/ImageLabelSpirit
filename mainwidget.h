#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QFile>
#include <QStandardItemModel>
#include <QWidget>

#include <module/importdialog.h>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
//    全局变量,即dialog弹出时父窗口蒙版指针
    static QWidget *g_masking ;
//    设置进度信息
    void setProcessInfo();
//    在主界面展示图片
    void displayImg();
//    初始化界面内容
    void initCustomUI();
//    初始化标注信息列表
    void initMarkInfo();

private slots:
    void on_pushButton_clicked();
    void on_openDirButton_clicked();
    void on_importButton_clicked();
    void on_settingButton_clicked();
    void on_exportButton_clicked();
    void on_moveButton_clicked();
    void on_narrowButton_clicked();
    void on_enlargeButton_clicked();
    void on_fullScreenButton_clicked();
    void on_reviewButton_clicked();
    void on_saveButton_clicked();
    void on_minimizeWindowButton_clicked();
    void on_customWindowButton_clicked();
    void on_closeWindowButton_clicked();
    void on_import_function(QString);
//    新的标注
    void addMark();

signals:
//    自定义信号,发送图片路径给导出窗口
    void sendExportLocalPath(QString);

protected:
//	窗口改变监听器
    void resizeEvent(QResizeEvent *event) ;



private:
    Ui::MainWidget *ui;
//   尚未浏览的图片 model对象
    QStandardItemModel *notReviewImgFilesItemModel;
//    已经浏览的图片 model对象
    QStandardItemModel *hasReviewImgFilesItemModel;
//    标注信息 model对象
    QStandardItemModel *markInfoItemModel;
//    标注信息 元数据 model对象(即:预定义的标注信息)
    QStandardItemModel *metaMarkInfoItemModel;
//    当前的Item指针对象
    QStandardItem *currentItem;
//    图片总数
    int imgCount = 0;
//    当前图片索引位置,从0开始
    int currentImg;
//    已标记图片数量
    int hasMarkCount = 0;
//    图片所在目录
    QString dirPath;

    ImportDialog *importDialog;

};

#endif // MAINWIDGET_H
