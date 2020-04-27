#pragma execution_character_set("utf-8")
#ifndef EXPORTMESSAGEBOX_H
#define EXPORTMESSAGEBOX_H

#include <QDialog>
#include <QStyle>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <common/commonutil.h>


namespace Ui {
class ExportMessageBox;
}

/**
 * 导出进度弹窗,主要是需要一个进度条,其实可以使用QProgressDialog 类来代替
 * @brief The ExportMessageBox class
 */
class ExportMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit ExportMessageBox(QString dir,QWidget *parent = nullptr);
    ~ExportMessageBox();
//    导出完成
    void export_complete();

private slots:
    void on_export_message_box_close_btn_clicked();

    void on_review_export_result_btn_clicked();
    void updateProgress();

protected:

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::ExportMessageBox *ui;
//    导出路径
    QString dirPath;
    QTimer *timer;

    QPoint last_mouse_position;
};

#endif // EXPORTMESSAGEBOX_H
