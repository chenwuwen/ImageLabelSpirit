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

/**
 * 等比压缩图片,并返回压缩比
 * @brief CommonUtil::compressProportion
 * @param pixmap
 * @param targetSize
 * @return
 */
double  CommonUtil::compressProportion(QPixmap& pixmap,QSize targetSize)
{
    QSize originalSize = pixmap.size();
    if(targetSize.width()>originalSize.width() && targetSize.height()>originalSize.height()){
        return 1.00;
    }
    double proportion = 0.0;
    if(originalSize.width()>originalSize.height()){
//    由于是保持长宽比的缩放,因此直接可以用宽度计算
        proportion = static_cast<double>(targetSize.width())/static_cast<double>(originalSize.width());
        qDebug() << "目标宽度："<< targetSize.width() <<"  实际宽度："<< originalSize.width() <<"  图片压缩比：" << proportion;
    }else{
        proportion = static_cast<double>(targetSize.height())/static_cast<double>(originalSize.height());
        qDebug() << "目标高度："<< targetSize.height() <<"  实际高度："<< originalSize.height() <<"  图片压缩比：" << proportion;
    }
//    缩放并保留长宽比
    pixmap =  pixmap.scaled(targetSize, Qt::KeepAspectRatio);
    return proportion;
}
