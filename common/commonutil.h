#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <QFileInfoList>
#include <QString>
#include <QWidget>



class CommonUtil
{

public:
    CommonUtil();
    static void setQssStyle(QString path,QWidget *widget);
    static QFileInfoList getImageFileInfoList(const QString& dirPath);
};

#endif // COMMONUTIL_H
