﻿#pragma execution_character_set("utf-8")
#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QStyle>
#include <QMetaEnum>
#include <QList>

#include <widgets/filebutton.h>
#include <custom/meta.h>
#include <common/commonutil.h>
#include <common/fontawesomeicons.h>
#include <widgets/filebutton.h>
#include <maininterface.h>


namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();


public slots:
    void on_close_export_dialog_btn_clicked();
    void on_exportFileButton_clicked();
    void setExportLocalPathAndMarkInfoCollection(QString,QMap<QString,QList<RectMetaInfo>>);


private slots:
    void on_determine_export_button_clicked();

    void on_push_btn_clicked();

signals:
//    信号,最终导出的文件路径和导出类型ID
    void sendExportPathAndExportId(QString,export_type);


private:
    Ui::ExportDialog *ui;
    FileButton *fileButton;
//    父窗口传过来的路径值
    QString localPath;
    QMap<QString,QList<RectMetaInfo>> markInfoCollection;
};

#endif // EXPORTDIALOG_H
