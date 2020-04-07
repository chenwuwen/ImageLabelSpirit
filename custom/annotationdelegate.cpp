#include "annotationdelegate.h"

#include <QComboBox>
#include <QDebug>

AnnotationDelegate::AnnotationDelegate(QObject *parent ):QStyledItemDelegate(parent)
{
    qDebug() << "AnnotationDelegate自定义委托构造函数执行";
}


QWidget *AnnotationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    qDebug() << "AnnotationDelegate自定义委托createEditor函数执行";
    QComboBox *cmb = new QComboBox();
    cmb->addItem("看云",NULL);
    cmb->addItem("无问",NULL);
    return cmb;
}



void AnnotationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "AnnotationDelegate自定义委托setEditorData函数执行";
    QComboBox *cmb = qobject_cast<QComboBox *>(editor);
    cmb->setCurrentText("kk");
}


void AnnotationDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     qDebug() << "AnnotationDelegate自定义委托setModelData函数执行";

     QComboBox *cmb = qobject_cast<QComboBox *>(editor);
     QString currentText = cmb->currentText();
//     设置模型值
     model->setData(index, currentText);
}


void AnnotationDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    qDebug() << "AnnotationDelegate自定义委托updateEditorGeometry函数执行";
}
