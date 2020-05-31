#include "annotationdelegate.h"
#include "meta.h"


AnnotationDelegate::AnnotationDelegate(QStringList metaDataList,QObject *parent):QStyledItemDelegate(parent),m_box(new QComboBox)
{
    qDebug() << "AnnotationDelegate自定义委托构造函数执行";
    this->metaDataList = metaDataList;
}


QWidget *AnnotationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    qDebug() << "AnnotationDelegate自定义委托createEditor函数执行";
//    这里创建Widget时,注意传入parent,否则会弹出一个新窗口来展示创建的Widget
    QComboBox *cmb = new QComboBox(parent);
//    往QComboBox中添加项
    cmb->addItems(metaDataList);
    cmb->setEditable(true);
    return cmb;
}



void AnnotationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "AnnotationDelegate自定义委托setEditorData函数执行";
    QString text = index.model()->data(index, Qt::EditRole).toString();
//    将*editor转换为QComboBox,转换成什么类型,要看createEditor方法中创建的是什么类型
    QComboBox *cmb = static_cast<QComboBox *>(editor);
    int tindex = cmb->findText(text);
    cmb->setCurrentIndex(tindex);
}


void AnnotationDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     qDebug() << "AnnotationDelegate自定义委托setModelData函数执行";

     QComboBox *cmb = static_cast<QComboBox *>(editor);
     QString currentText = cmb->currentText();
     qDebug() << "当前信息为：" << currentText;
//     设置模型值
     QVariant va = model->data(index);
     RectMetaInfo rectMeta = va.value<RectMetaInfo>();
     rectMeta.text = currentText;
//     第二个参数应为基本类型,否则无法显示
     model->setData(index, currentText,Qt::EditRole);
}


void AnnotationDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    qDebug() << "AnnotationDelegate自定义委托updateEditorGeometry函数执行" << option.rect;
    editor->setGeometry(option.rect);
}

//void AnnotationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    int radio = 4;
//    int top = option.rect.top() + radio;
//    int left = option.rect.left() + radio;
//    int width = option.rect.width() - 2 * radio;
//    int height = option.rect.height() - 2 * radio;


//    QStyleOptionComboBox box;
//    box.rect.setRect(left,top,width,height);
//    box.state  = QStyle::State_Enabled;
//    box.editable = false;
////    设置画上的QCombobox的展示信息
//    box.currentText = index.data().value<RectMeta>().text;
//    qDebug() << "设置显示的值" << index.data();
////  参数说明：https://www.cnblogs.com/lifexy/p/9186565.html
//    QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel,
//                                        &box,
//                                        painter,m_box);
//}

bool AnnotationDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonDblClick){
//             禁止双击编辑
               return true;
    }
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}
