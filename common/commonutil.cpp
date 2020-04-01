#include "commonutil.h"

#include <QFile>
#include <QString>
#include <QWidget>
#include <QDebug>
#include <QFileInfoList>
#include <QDir>

CommonUtil::CommonUtil()
{

}
/**
 * 设置widget的样式
 * @brief setQssStyle
 * @param path  资源文件 :/** 形式
 * @param widget  哪个widget
 */
void CommonUtil::setQssStyle(QString path,QWidget *widget)
{
    qDebug() << "设置qss样式";
    QFile file(path);
    file.open(QFile::ReadOnly);
    widget->setStyleSheet(file.readAll());
    file.close();
}

/**
 * 读取qss样式文件
 * @brief CommonUtil::readQssFile
 * @param filePath
 * @return
 */
QString CommonUtil::readQssFile(const QString& filePath)
{
    QString strStyleSheet = "";
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        strStyleSheet = QLatin1String(file.readAll());
    }
    return  strStyleSheet;
}

/**
 * 获取指定路径下的图片文件信息列表
 * @brief getImageFileInfoList
 * @param dirPath
 * @return
 */
QFileInfoList CommonUtil::getImageFileInfoList(const QString& dirPath)
{
    QDir dir(dirPath);
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg" << "*.jpeg";
    return dir.entryInfoList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
}
