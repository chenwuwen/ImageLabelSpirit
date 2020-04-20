#pragma execution_character_set("utf-8")
#ifndef ANNOTATIONDELEGATE_H
#define ANNOTATIONDELEGATE_H

#include <QStyledItemDelegate>



class AnnotationDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AnnotationDelegate(QObject *parent = 0);
//    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    创建你编辑时候的控件,双击调用
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    编辑的时候设置数据到上面创建的editor中。
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    编辑完成，保存数据到data中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//    设置编辑控件的位置和大小。样式等
//    void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // ANNOTATIONDELEGATE_H
