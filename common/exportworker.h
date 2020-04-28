#pragma execution_character_set("utf-8")
#ifndef EXPORTWORKER_H
#define EXPORTWORKER_H

#include <QObject>
#include <custom/meta.h>
#include <unistd.h>
#include <windows.h>
/**
 * 多线程 工作类 用于导出
 * @brief The ExportWorker class
 */
class ExportWorker : public QObject
{
    Q_OBJECT
public:
    explicit ExportWorker(QString dirPath,export_type exportType,QMap<QString,QList<RectMetaInfo>> data,QObject *parent = nullptr);

signals:
    void complete();

public slots:

    void exportMarkData();

private:
    QString savePath;
    export_type exportButtonId;
    QMap<QString,QList<RectMetaInfo>> markInfoCollection;
};

#endif // EXPORTWORKER_H
