#include "annotationdelegate.h"




AnnotationDelegate::AnnotationDelegate(QStringList metaDataList,QObject *parent):QStyledItemDelegate(parent)
{
    qDebug() << "AnnotationDelegate自定义委托构造函数执行";
    this->metaDataList = metaDataList;
}


QWidget *AnnotationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    qDebug() << "AnnotationDelegate自定义委托createEditor函数执行";
//    这里创建Widget时,注意传入parent,否则会弹出一个新窗口来展示创建的Widget
    AnnotationComboBox *cmb = new AnnotationComboBox(parent);
//    往QComboBox中添加项
    cmb->addItems(metaDataList);
    return cmb;
}



//void AnnotationDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    qDebug() << "AnnotationDelegate自定义委托setEditorData函数执行";
//    QString text = index.model()->data(index, Qt::EditRole).toString();
////    将*editor转换为QComboBox,转换成什么类型,要看createEditor方法中创建的是什么类型
//    QComboBox *cmb = static_cast<QComboBox *>(editor);
//    int tindex = cmb->findText(text);
//    cmb->setCurrentIndex(tindex);
//}


void AnnotationDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const
{
     qDebug() << "AnnotationDelegate自定义委托setModelData函数执行";

     AnnotationComboBox *cmb = static_cast<AnnotationComboBox *>(editor);
     QString currentText = cmb->currentText();


//     此处的model的data()值返回的是QStandardItem类的setText()的值
     QString srcStr = model->data(index).toString();


//     第二个参数应为基本类型,否则无法显示
     model->setData(index, currentText,Qt::EditRole);


     if (srcStr != currentText){
         qDebug() << "当前信息为：" << currentText  << "原值：" <<  srcStr  << " 发送改变信息号";
         emit markTextInfoUpdate(currentText,index);
     }

}


void AnnotationDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    qDebug() << "AnnotationDelegate自定义委托updateEditorGeometry函数执行" << option.rect;
    editor->setGeometry(option.rect);
}

void AnnotationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int radio = 4;
    int top = option.rect.top() + radio;
    int left = option.rect.left() + radio;
    int width = option.rect.width() - 2 * radio;
    int height = option.rect.height() - 2 * radio;


    QStyleOptionComboBox box;
    box.rect.setRect(left,top,width,height);
    box.state = option.state;
    box.state |= QStyle::State_Enabled;
    box.editable = false;
//    设置画上的QCombobox的展示信息
    box.currentText = index.data().toString();
//  参数说明：https://www.cnblogs.com/lifexy/p/9186565.html
//    注意：下面两个draw*方法都要写,第一个draw方法是画下拉框的,第二个draw方法是画下拉框中当前显示的文字的
    QApplication::style()->drawComplexControl(QStyle::CC_ComboBox,
                                        &box,
                                        painter);
    QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, &box, painter);

}

bool AnnotationDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{

//    还原鼠标样式
//    QApplication::restoreOverrideCursor();
    switch (event->type()) {
        case QEvent::MouseMove:{
//              设置鼠标样式为手型
                QApplication::setOverrideCursor(Qt::PointingHandCursor);
                return true;
          }

        case QEvent::MouseButtonPress:{
//           鼠标按下
             return false;
          }

        default:
            return QStyledItemDelegate::editorEvent(event,model,option,index);
    }

}
