#include "commonutil.h"




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
qreal CommonUtil::compressProportion(QPixmap& pixmap,QSize targetSize)
{
    QSize originalSize = pixmap.size();
    if(targetSize.width()>originalSize.width() && targetSize.height()>originalSize.height()){
        return 1.00;
    }
    qreal proportion = 0.0;
    if(originalSize.width()>originalSize.height()){
//    由于是保持长宽比的缩放,因此直接可以用宽度计算
        proportion = static_cast<qreal>(targetSize.width())/static_cast<qreal>(originalSize.width());
        qDebug() << "目标宽度：" << targetSize.width() << "  实际宽度："<< originalSize.width() << "  图片压缩比：" << proportion;
    }else{
        proportion = static_cast<qreal>(targetSize.height())/static_cast<qreal>(originalSize.height());
        qDebug() << "目标高度：" << targetSize.height() <<"  实际高度：" << originalSize.height() <<"  图片压缩比：" << proportion;
    }
//    缩放并保留长宽比
    pixmap =  pixmap.scaled(targetSize, Qt::KeepAspectRatio);
    return proportion;
}

/**
 * 加载图片得到图片尺寸,同时知道了目标的尺寸,从而计算出默认的展示尺寸
 * @brief CommonUtil::defaultDisplayQRectF
 * @param pixmapPath
 * @param targetSize 目标的尺寸
 * @return
 */
QRectF CommonUtil::defaultDisplayQRectF(const QString pixmapPath,QSize targetSize)
{
    QPixmap pixmap(pixmapPath);
    QSize originalSize = pixmap.size();

    if(targetSize.width()>originalSize.width() && targetSize.height()>originalSize.height()){
        return  pixmap.rect();
    }
//    缩放并保留长宽比
    pixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio);
    return  pixmap.rect();
}

void CommonUtil::saveJSonValue(const QMap<QString, QList<RectMetaInfo> > mapCollection,QString savePath)
{
    QJsonDocument document;
    foreach(const QString key,mapCollection.keys()){
         QJsonArray object;
         QJsonObject outputs;
         QList<RectMetaInfo> list = mapCollection[key];
         for(RectMetaInfo rectMeta: list){
//             一个标注
             QJsonObject item;
//             标注中的位置尺寸信息
             QJsonObject pos;

             pos.insert("x",static_cast<int>(rectMeta.x));
             pos.insert("y",static_cast<int>(rectMeta.y));
             pos.insert("w",static_cast<int>(rectMeta.w));
             pos.insert("h",static_cast<int>(rectMeta.h));

             item.insert("name",rectMeta.text);
             item.insert("bndbox",pos);

             object.append(item);
         }

         outputs.insert("object",object);

//         根json
         QJsonObject root;
         root.insert("path",key);
         root.insert("outputs",outputs);
         root.insert("time_labeled",QDateTime::currentDateTime().toString());
         root.insert("labeled",list.size()>0);

         QPixmap pixmap(key);

//         尺寸
         QJsonObject size;
         size.insert("width",pixmap.width());
         size.insert("height",pixmap.height());
         size.insert("depth",pixmap.depth());

         root.insert("size",size);

         document.setObject(root);
         QFileInfo fileInfo(key);
//         得到的文件名称是不带后缀的名称
         QString fileName = fileInfo.baseName();
         QFile file(savePath + fileName + ".json");

         QDir saveDir(savePath);
         if(!saveDir.exists()){
           qDebug() << "文件夹不存在,创建文件夹" ;
           saveDir.mkdir(savePath);
         }
         qDebug() << "导出文件的绝对路径：" << file.fileName();
//         以读写方式打开目录下的文件，若该文件不存在则会自动创建
         file.open(QIODevice::ReadWrite);
//         将json写入文件中去
         file.write(document.toJson());
         file.close();
    }
}

void CommonUtil::readJSonValue(QMap<QString, QList<RectMetaInfo>> &collection, QString dirPath)
{
    QDir dir(dirPath);
    QStringList nameFilters;
    nameFilters << "*.json" ;
    QFileInfoList fileInfoList =  dir.entryInfoList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    qDebug() << "读取到的Json文件数量为:" << fileInfoList.size();
    QJsonParseError complex_json_error;
    QJsonDocument document;
    foreach(const QFileInfo fileInfo , fileInfoList){
        QList<RectMetaInfo> rectInfos;
//        读取文件
        QFile file(fileInfo.absoluteFilePath());

//        只读方式打开
        file.open(QFile::ReadOnly);

//       读取为json
        document = QJsonDocument::fromJson(file.readAll(), &complex_json_error);

        if(complex_json_error.error == QJsonParseError::NoError){
            QJsonObject root = document.object();

            QJsonValue pathJsonValue = root.value("path");
            QString path = pathJsonValue.toVariant().toString();

            QJsonValue outputsJsonValue = root.value("outputs");

    //         判断outputsJsonValue是不是QJsonObject对象
             if(outputsJsonValue.isObject()){

               QJsonObject outputs = outputsJsonValue.toVariant().toJsonObject();

    //           判断outputsJsonValue是否包含object key
               if (outputs.contains("object")){
                  QJsonValue objectJsonValue = outputs.value("object");

    //              判断objectJsonValue是否是QJsonArray类型
                  if( objectJsonValue.isArray() ){
                       QJsonArray array = objectJsonValue.toArray();
                       if(!array.empty()){
                           for (int i = 0 ;i <array.size();i++){
                             QJsonValue value =  array.at(i);
                             QJsonObject vo = value.toObject();
                             QString text = vo.value("name").toString();
                             QJsonObject bndbox = vo.value("bndbox").toObject();
//                             QVariant bndbox = vo.value("bndbox").toVariant();
//                             RectMetaInfo rectMeta = bndbox.value<RectMetaInfo>();
                             RectMetaInfo rectMeta;
                             rectMeta.x =  bndbox.value("x").toInt();
                             rectMeta.y =  bndbox.value("y").toInt();
                             rectMeta.w =  bndbox.value("w").toInt();
                             rectMeta.h =  bndbox.value("h").toInt();
                             rectMeta.text = text;

                             rectInfos << rectMeta;
                           }
                       }
                  }

               }

             }
            collection[path] = rectInfos;
        }else{
            qDebug() << "读取JSON文件出错：" << fileInfo.absoluteFilePath() << " 错误类型：" << complex_json_error.error;
        }

    }

    qDebug() << "读取JSON数据完毕,数据量为：" << collection.size();
}

void CommonUtil::saveXmlValue(const QMap<QString, QList<RectMetaInfo>> map, QString savePath)
{


    foreach(const QString key,map.keys()){

       QDomDocument doc;

       QDomProcessingInstruction instruction;

//     写入xml头部
       instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
       doc.appendChild(instruction);
//     添加根节点
       QDomElement root=doc.createElement("doc");
       doc.appendChild(root);

//     添加第一个子节点及其子元素
       QDomElement path=doc.createElement("path");
//       将值设置到tag中
       path.appendChild(doc.createTextNode(key));

//     方式二：创建属性 值必须是字符串
       QDomElement time_labeled = doc.createElement("time_labeled");
       time_labeled.appendChild(doc.createTextNode(QDateTime::currentDateTime().toString()));

       QDomElement labeled=doc.createElement("labeled");
       labeled.appendChild(doc.createTextNode(map[key].size()>0?"true":"false"));

       QDomElement outputs=doc.createElement("outputs");

       QDomElement object=doc.createElement("object");

       QList<RectMetaInfo> rectMetaInfoList = map[key];
       for(RectMetaInfo rectMeta:rectMetaInfoList){
           QDomElement item=doc.createElement("item");


           QDomElement name=doc.createElement("name");
           name.appendChild(doc.createTextNode(rectMeta.text));

           QDomElement bndbox=doc.createElement("bndbox");

//           位置尺寸信息
           QDomElement x=doc.createElement("x");
           x.appendChild(doc.createTextNode(QString::number(static_cast<int>(rectMeta.x))));

           QDomElement y=doc.createElement("y");
           y.appendChild(doc.createTextNode(QString::number(static_cast<int>(rectMeta.y))));

           QDomElement w=doc.createElement("w");
           w.appendChild(doc.createTextNode(QString::number(static_cast<int>(rectMeta.w))));

           QDomElement h=doc.createElement("h");
           h.appendChild(doc.createTextNode(QString::number(static_cast<int>(rectMeta.h))));

//           添加子元素
           bndbox.appendChild(x);
           bndbox.appendChild(y);
           bndbox.appendChild(w);
           bndbox.appendChild(h);

           item.appendChild(name);
           item.appendChild(bndbox);
           object.appendChild(item);
       }

       outputs.appendChild(object);

//       尺寸
       QDomElement size=doc.createElement("size");

       QPixmap pixmap(key);
       QDomElement width=doc.createElement("width");
       width.appendChild(doc.createTextNode(QString::number(pixmap.width())));
       QDomElement height=doc.createElement("height");
       height.appendChild(doc.createTextNode(QString::number(pixmap.height())));
       QDomElement depth=doc.createElement("depth");
       depth.appendChild(doc.createTextNode(QString::number(pixmap.depth())));

       size.appendChild(width);
       size.appendChild(height);
       size.appendChild(depth);


       root.appendChild(path);
       root.appendChild(outputs);
       root.appendChild(time_labeled);
       root.appendChild(labeled);
       root.appendChild(size);

       QFileInfo fileInfo(key);
//         得到的文件名称是不带后缀的名称
       QString fileName = fileInfo.baseName();
       QFile file(savePath + fileName + ".xml");

       QDir saveDir(savePath);
       if(!saveDir.exists()){
         qDebug() << "文件夹不存在,创建文件夹" ;
         saveDir.mkdir(savePath);
       }
       qDebug() << "导出文件的绝对路径：" << file.fileName();
//      以读写方式打开目录下的文件，若该文件不存在则会自动创建 QFile::Truncate表示清空原来的内容
       file.open(QIODevice::ReadWrite|QFile::Truncate);
//       输出到文件
       QTextStream out_stream(&file);
//       缩进4格
       doc.save(out_stream,4);
       file.close();
    }
}

void CommonUtil::readXmlValue(QMap<QString, QList<RectMetaInfo>> &collection, QString dirPath)
{
    QDir dir(dirPath);
    QStringList nameFilters;
    nameFilters << "*.xml" ;
    QFileInfoList fileInfoList =  dir.entryInfoList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    qDebug() << "读取到的Xml文件数量为:" << fileInfoList.size();
    QDomDocument doc;
    foreach(const QFileInfo fileInfo , fileInfoList){
        QList<RectMetaInfo> rectInfos;
        QString path ;
//        读取文件
        QFile file(fileInfo.absoluteFilePath());

//        只读方式打开
        file.open(QFile::ReadOnly);
//        setContent()函数来设置整个文档的内容，它会将XML解析成一个DOM树,并保存在内存中
        if(!doc.setContent(&file)){
            file.close();
            continue;
        }
        file.close();

//        返回根节点
        QDomElement root=doc.documentElement();
//        得到根节点下的所有子节点
        QDomNodeList domNodeList = root.childNodes();


        for (int i=0;i<domNodeList.count();i++){
            QDomNode domNode = domNodeList.at(i);
            QString nodeName = domNode.nodeName();
            if (nodeName == "path"){
//                取出tag中的值 即： <path>123</path> 取出123
                path = domNode.toElement().text();
            }

            if (nodeName == "outputs"){
                QDomNode objectNode = domNode.childNodes().at(0);
                QDomNodeList objectNodeList = objectNode.childNodes();
                if (objectNodeList.count() > 0){
                    for(int k = 0; k<objectNodeList.count(); k++){
                       QDomNode itemNode = objectNodeList.at(k);
                       QDomNodeList itemNodeList  = itemNode.childNodes();
                       RectMetaInfo rectMeta;
                       for (int j = 0;j<itemNodeList.count();j++) {
                           QDomNode domNode = itemNodeList.at(j);
                           if (domNode.nodeName() == "name"){
                               rectMeta.text = domNode.toElement().text();
                           }else{
                               QDomNodeList nodeList = domNode.childNodes();
                               for(int n=0; n<nodeList.count();n++){
                                   QDomNode node = nodeList.at(n);
                                   if(node.nodeName() == "x"){
                                       rectMeta.x = node.toElement().text().toInt();
                                       continue;
                                   }
                                   if(node.nodeName() == "y"){
                                       rectMeta.y = node.toElement().text().toInt();
                                       continue;
                                   }
                                   if(node.nodeName() == "w"){
                                       rectMeta.w = node.toElement().text().toInt();
                                       continue;
                                   }
                                   if(node.nodeName() == "h"){
                                       rectMeta.h = node.toElement().text().toInt();
                                       continue;
                                   }
                               }
                           }
                       }
                       rectInfos << rectMeta;
                    }

                }
            }
        }
        collection[path] = rectInfos;
     }
}


