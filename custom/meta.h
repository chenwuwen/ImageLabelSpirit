#ifndef META_H
#define META_H

#include <QString>
#include <QMetaType>

//对于自定义数据类型，如果要使用QVariant，必须使用Q_DECLARE_METATYPE注册。
//https://www.jianshu.com/p/670de4f63689?from=groupmessage

//矩形坐标信息
typedef struct RectMetaInfo{
    QString name;
    int x;
    int y;
    int w;
    int h;
} RectMeta;

Q_DECLARE_METATYPE(RectMetaInfo);

#endif // META_H
