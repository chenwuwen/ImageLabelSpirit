#pragma execution_character_set("utf-8")
#ifndef FILELISTDELEGATE_H
#define FILELISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QDebug>
#include <QPainter>
class FileListDelegate : public QStyledItemDelegate
{
public:
    FileListDelegate(QWidget* parent = 0);

//    绘制控件
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


private:
    QWidget *parentWdiget;

};

#endif // FILELISTDELEGATE_H
