#pragma execution_character_set("utf-8")
#ifndef META_H
#define META_H

#include <QString>
#include <QMetaType>
#include <QDebug>

//对于自定义数据类型，如果要使用QVariant，必须使用Q_DECLARE_METATYPE注册。
//https://www.jianshu.com/p/670de4f63689?from=groupmessage

//矩形坐标信息
typedef struct RectMetaInfo{
    QString text;
    qreal x;
    qreal y;
    qreal w;
    qreal h;

//    默认结构体是无法使用 == 判断相等的.因此重载运算符
    bool operator==(const RectMetaInfo& rect)
    {
        return (x == rect.x) && (y == rect.y) && (w == rect.w) && (h == rect.h) && (text == rect.text);
    }

} RectMeta;


//qDebug() 不能打印自定义结构体,解决方法就是重载<< 运算符
QDebug inline operator<<(QDebug debug, const RectMetaInfo &rect)
{
    debug << QString("名称：%1,位置信息：[%2,%3,%4,%5]").arg(rect.text).arg(rect.x).arg(rect.y).arg(rect.w).arg(rect.h);
    return debug;
}

Q_DECLARE_METATYPE(RectMetaInfo);

//导出方式枚举
enum export_type{
    JSON,
    XML,
    MONGO
};

//项目信息

typedef struct ProjectInfo{
    QString projectName;
    QString imgPath;
    QString annotationMeta;
    QString createTime;
//    这里使用了QVariant而不是QList<RectMeta>,是因为使用QDataStream序列化不支持这种格式,因此使用QVariant来转换
    QMap<QString,QVariant> markCollection;
} Project;
Q_DECLARE_METATYPE(ProjectInfo);

//重载序列化
inline QDataStream &operator<<(QDataStream &output , const ProjectInfo &pj)
{

    output << pj.projectName << pj.imgPath << pj.annotationMeta << pj.createTime << pj.markCollection;
    return output ;
}
//重载反序列化
inline QDataStream &operator>>(QDataStream &input , ProjectInfo &pj)
{

    input >> pj.projectName >> pj.imgPath >> pj.annotationMeta >> pj.createTime ;
    return input ;
}



#endif // META_H
