#pragma execution_character_set("utf-8")
#ifndef META_H
#define META_H

#include <QString>
#include <QMetaType>
#include <QDebug>
#include <QDataStream>

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
Q_DECLARE_METATYPE(RectMetaInfo);

//qDebug() 不能打印自定义结构体,解决方法就是重载<< 运算符
QDebug inline operator<<(QDebug debug, const RectMetaInfo &rect)
{
    debug << QString("名称：%1,位置信息：[%2,%3,%4,%5]").arg(rect.text).arg(rect.x).arg(rect.y).arg(rect.w).arg(rect.h);
    return debug;
}

//重载序列化
inline QDataStream &operator<<(QDataStream &output , const RectMetaInfo &metaInfo)
{

//        转换成字符串并保留两位小数,四舍五入
//        x = QString::number(metaInfo.x,'d',2);
//        y = QString::number(metaInfo.y,'d',2);
//        w = QString::number(metaInfo.w,'d',2);
//        h = QString::number(metaInfo.h,'d',2);
        output << metaInfo.text << metaInfo.x << metaInfo.y << metaInfo.w << metaInfo.h;

        return output;
}

//重载反序列化
inline QDataStream &operator>>(QDataStream &input , RectMetaInfo &metaInfo)
{
    input >> metaInfo.text >> metaInfo.x >> metaInfo.y >> metaInfo.w >> metaInfo.h;
    return input;
}


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
    int currentImgIndex;
    QMap<QString,QList<RectMeta>> markCollection;
} Project;
Q_DECLARE_METATYPE(ProjectInfo);

//重载序列化
inline QDataStream &operator<<(QDataStream &output , const ProjectInfo &pj)
{

    output << pj.projectName << pj.imgPath << pj.annotationMeta << pj.createTime << pj.currentImgIndex;
//    附加信息 QMap<int,int> 可以直接被序列化（QMap能否被直接序列化,要看QMap中的类型是否是基本类型,如果是,就可以直接序列化）,第一个参数表示第几个key,第二个参数表示该key下存放的数据的数量
    QMap<int,int> collectionPreview;
    int k_index = 0;
    foreach(QString key,pj.markCollection.keys()){
        collectionPreview[k_index] = pj.markCollection[key].size();
        k_index++;
    }
    qDebug() << "序列化集合的概览：" << collectionPreview;
//    序列化QMap时需要注意,头文件中需要引入 QDataStream 依赖,否则此处报错
    output << collectionPreview;

    foreach(QString key,pj.markCollection.keys()){
        QList<RectMetaInfo> rectMetas = pj.markCollection[key];
//        如果map当前key的value是空,则不序列化key
        if (rectMetas.size() == 0) continue;
        output << key;
        for(RectMetaInfo rectMetaInfo : rectMetas){
            output << rectMetaInfo;
        };

    }

    return output ;
}
//重载反序列化
inline QDataStream &operator>>(QDataStream &input , ProjectInfo &pj)
{

    input >> pj.projectName >> pj.imgPath >> pj.annotationMeta >> pj.createTime >> pj.currentImgIndex;
    QMap<int,int> collectionPreview;
    input >> collectionPreview;
//    qDebug() << "反序列化集合的概览：" << collectionPreview;
    QMap<QString,QList<RectMetaInfo>> collection;
    for (int i = 0;i< collectionPreview.size();i++){
        if ( collectionPreview[i] == 0 ) continue;
        QString key;
        input >> key;
        QList<RectMetaInfo> rectInfoList;
        for (int j = 0; j < collectionPreview[i] ; j++){
            RectMetaInfo rectMetaInfo;
            input >> rectMetaInfo;
            rectInfoList.append(rectMetaInfo);
        }
        collection[key] = rectInfoList;
    }
    pj.markCollection = collection;
    return input ;
}



#endif // META_H
