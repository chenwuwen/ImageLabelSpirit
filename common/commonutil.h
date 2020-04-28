#pragma execution_character_set("utf-8")
#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <QFileInfoList>
#include <QMap>
#include <QString>
#include <QWidget>
#include <custom/meta.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QFileInfoList>
#include <QDir>
#include <QDateTime>
#include <QPixmap>
#include <QDomDocument>
#include <QDomNodeList>
#include <QStandardPaths>

class CommonUtil
{

public:

    static void setQssStyle(QString path,QWidget *widget);
    static QFileInfoList getImageFileInfoList(const QString& dirPath);
    static QFileInfoList getProjectInfoList();
    static void saveProjectInfo(Project project);
    static Project readProjectInfo(QString projectFilePath);
    static QString readQssFile(const QString& filePath);
    static qreal compressProportion(QPixmap& pixmap,QSize targetSize);
    static QRectF defaultDisplayQRectF(const QString pixmapPath,QSize targetSize);
    static void saveJSonValue(const QMap<QString,QList<RectMetaInfo>> map, QString savePath);
    static void readJSonValue(QMap<QString,QList<RectMetaInfo>> &collection, QString dirPath);
    static void saveXmlValue(const QMap<QString,QList<RectMetaInfo>> map, QString savePath);
    static void readXmlValue(QMap<QString,QList<RectMetaInfo>> &collection, QString dirPath);

private:
    CommonUtil();
    ~CommonUtil();
//    所有项目信息的存放路径
    static QString PROJECT_STORAGE_DIR;

};

#endif // COMMONUTIL_H
