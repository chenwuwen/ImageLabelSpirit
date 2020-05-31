#pragma execution_character_set("utf-8")
#ifndef ANNOTATIONDELEGATE_H
#define ANNOTATIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>


#include <QComboBox>
#include <QDebug>
#include <QPainter>

class AnnotationDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AnnotationDelegate(QStringList metaDataList,QObject *parent = 0);

//    创建你编辑时候的控件,双击调用
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//    显示控件后设置里面的值,也就是上面createEditor方法执行完成后里面设置的值
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

//    将数据写入到模型中,编辑完成，保存数据到data中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

//    设置编辑控件的位置和大小。样式等
    void updateEditorGeometry (QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

//    之前我们写的自定义委托,每次都需要双击某个数据项,才能弹出编辑器,那如何让委托一直呈现在视图显示上呢？步骤如下:
//    重写委托类的paint成员函数
//    在paint()中,通过QApplication::style()->drawControl()来自定义数据显示方式,比如绘制按钮
//    重写委托类的editorEvent成员函数
//    在editorEvent中处理交互事件,比如判断鼠标是否双击,以及更改模型数据等
//    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    bool editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index );

private:
    QStringList metaDataList;
    QComboBox *m_box;
};

#endif // ANNOTATIONDELEGATE_H
