#ifndef FILELISTDELEGATE_H
#define FILELISTDELEGATE_H

#include <QStyledItemDelegate>

#include <QApplication>
#include <QItemDelegate>
#include <QDebug>
#include <QPainter>
class FileListDelegate : public QItemDelegate
{
public:
    FileListDelegate(QObject* parent = 0);

//    绘制控件
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // FILELISTDELEGATE_H
