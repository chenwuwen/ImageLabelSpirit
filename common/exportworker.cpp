#include "commonutil.h"
#include "exportworker.h"

ExportWorker::ExportWorker(QString dirPath,export_type exportType,QMap<QString,QList<RectMetaInfo>> data,QObject *parent) : QObject(parent)
{
    this->exportButtonId = exportType;
    this->markInfoCollection = data;

//    得到路径分隔符
    QChar separ = QDir::separator();
//   QDir::toNativeSeparators() 方法,得到转换后的路径
    savePath = QDir::toNativeSeparators(dirPath);
    qDebug() << "处理后的导出路径为：" << savePath;
}

void ExportWorker::exportMarkData()
{
//    如果使用vc编译，需要引入windows.h,且函数名为Sleep(),单位为毫秒;
    sleep(3);
//    Sleep(3000);
    switch (exportButtonId) {
        case export_type::JSON:
            qDebug() << "导出为JSON形式";
            CommonUtil::saveJSonValue(markInfoCollection,savePath);
            break;
        case export_type::XML:
            qDebug() << "导出为XML形式";
            CommonUtil::saveXmlValue(markInfoCollection,savePath);
            break;
        case export_type::MONGO:
            qDebug() << "导出为MONGO形式";
            break;
    }
    emit complete();
}
