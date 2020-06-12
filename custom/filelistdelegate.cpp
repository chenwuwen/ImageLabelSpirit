#include "filelistdelegate.h"



FileListDelegate::FileListDelegate(QWidget* parent):QStyledItemDelegate(parent)
{

}





void FileListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
//    qDebug() << "FileListDelegate paint() 执行";
//	得到Item中设置的数据,需要注意第二个参数,设置数据时的UserRole与取出数据的UserRoel应该一致
    QVariant v = index.model()->data(index,Qt::UserRole + 1);
    QString path = v.toString();
//    qDebug() << "得到数据：" << path;
    if(path.isEmpty()) {
//        qDebug() << "调用了默认委托" ;
//		调用默认委托(即调用父类方法)
        QStyledItemDelegate::paint(painter,option,index);
    } else {
        QPixmap pixmap(path);
        QRect rect = option.rect;
//        qDebug() << "文件列表自定义委托,各个Item展示的信息：(" << rect.x() << " " << rect.y() << "   " << rect.width() << "  " << rect.height() << ")";
        painter->save();
//		绘图抗锯齿
        painter->setRenderHint(QPainter::Antialiasing);
//		pixmap等比压缩
        pixmap = pixmap.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//		设置背景色(黑色)
        painter->setBrush(QBrush(QColor(0,0,0)));
        painter->drawRect(rect);
//		找到画图的坐标原点
        int x = rect.x() + (rect.width() - pixmap.width()) / 2;
        int y = rect.y() + (rect.height() - pixmap.height()) / 2;
        painter->drawPixmap(x,y,pixmap);
        painter->restore();
    }
}
