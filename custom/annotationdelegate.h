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
//    显示控件后设置里面的值,也就是上面createEditor方法执行完成后里面设置的值
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    编辑完成，保存数据到data中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//    设置编辑控件的位置和大小。样式等
//    void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // ANNOTATIONDELEGATE_H
