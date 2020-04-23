#include "filelistdelegate.h"

FileListDelegate::FileListDelegate(QObject* parent):QItemDelegate(parent)
{

}

void FileListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
      qDebug() << "FileListDelegate paint() 执行";
      QVariant v = index.model()->data(index,Qt::UserRole + 1);
      QString path = v.toString();
      qDebug() << "取到图片路径：" << path;
      QPixmap pixmap(path);
//    获取项风格设置
      QStyleOptionViewItem iconOption = option;
      iconOption.displayAlignment = Qt::AlignCenter | Qt::AlignVCenter;

      QRect parentRect = iconOption.rect;
//      pixmap等比压缩
      pixmap.scaled(parentRect.width(), parentRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

      int pixmapHeight = pixmap.size().height();
//      绘图抗锯齿
      painter->setRenderHint(QPainter::Antialiasing);

//      painter->drawPixmap(pixmap,)

//      画图片
//      QApplication::style()->drawItemPixmap(painter,iconOption.rect,iconOption.displayAlignment,pixmap);

}
