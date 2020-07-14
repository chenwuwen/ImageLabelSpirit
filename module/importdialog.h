#pragma execution_character_set("utf-8")
#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>

#include <widgets/filebutton.h>
#include <QFileDialog>
#include <QStandardPaths>

#include <common/commonutil.h>
#include <common/fontawesomeicons.h>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();
    void on_importFileButton_clicked();

//    事件过滤器:watched:代表被监控的组件  event:代表要转发的事件
//    返回true,表示该事件也被过滤掉(处理),无需再转发了
//    返回false,则正常转发给watched
//    https://www.cnblogs.com/lifexy/p/8996425.html
    bool eventFilter(QObject *obj, QEvent *event);

    void closeEvent(QCloseEvent *event);

private slots:

    void on_determine_import_button_clicked();


signals:
//    自定义信号,发送数据给父窗口
    void sendData(QString);

private:
    Ui::ImportDialog *ui;
    FileButton *fileButton;
    QString dirPath ;
};

#endif // IMPORTDIALOG_H
