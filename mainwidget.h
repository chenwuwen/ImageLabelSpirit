#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QFile>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
//    设置进度信息
    void setProcessInfo();
//    在主界面展示图片
    void displayImg();

private slots:
    void on_pushButton_clicked();
    void on_openDirButton_clicked();
    void on_importButton_clicked();
    void on_settingButton_clicked();
    void on_exportButton_clicked();
    void on_moveButton_clicked();



private:
    Ui::MainWidget *ui;
//   图片 model对象
    QStandardItemModel *imgFilesItemModel;
//    图片总数
    int imgCount;
//    当前图片索引位置,从0开始
    int currentImg;
//    已标记图片数量
    int hasMarkCount = 0;

};

#endif // MAINWIDGET_H
