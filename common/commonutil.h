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

class CommonUtil
{

public:
    CommonUtil();
    static void setQssStyle(QString path,QWidget *widget);
    static QFileInfoList getImageFileInfoList(const QString& dirPath);
    static QString readQssFile(const QString& filePath);
    static qreal compressProportion(QPixmap& pixmap,QSize targetSize);
    static QRectF defaultDisplayQRectF(const QString pixmapPath,QSize targetSize);
    static void saveJSonValue(QMap<QString,QList<RectMetaInfo>> map, QString savePath);
    static void readJSonValue(QMap<QString,QList<RectMetaInfo>> &collection, QString dirPath);
};

#endif // COMMONUTIL_H
