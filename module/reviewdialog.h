﻿#pragma execution_character_set("utf-8")
#ifndef REVIEWDIALOG_H
#define REVIEWDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <custom/meta.h>
#include <common/commonutil.h>

namespace Ui {
class ReviewDialog;
}

class ReviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReviewDialog(QWidget *parent = nullptr);
    ~ReviewDialog();
    void setMarkInfoTable(QMap<QString,QList<RectMetaInfo>>);

public slots:
     void setExportLocalPath(QString localPath);

private slots:

    void on_review_dialog_export_btn_clicked();

    void on_review_dialog_close_btn_clicked();

private:
    Ui::ReviewDialog *ui;
    QStandardItemModel *tableItemModel;
    QString localPath;
    QMap<QString,QList<RectMetaInfo>> collection;
};

#endif // REVIEWDIALOG_H
