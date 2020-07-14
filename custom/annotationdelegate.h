#pragma execution_character_set("utf-8")
#ifndef ANNOTATIONDELEGATE_H
#define ANNOTATIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QPainter>

#include <widgets/annotationcombobox.h>
#include "meta.h"

//我们以编辑某个数据项为例:
//视图首先会调用createEditor()函数生成编辑器
//调用updateEditorGeometry()函数设置编辑器组件大小
//调用setEditorData()函数,将模型里的数据提取到编辑器中
//等待用户编辑... ...
//当用户编辑完成后, 系统将会发送commitData信号函数
//然后调用setModelData()函数,设置模型数据,以及setEditorData()函数,更新编辑器
//视图最后发送closeEditor()信号函数,表示已关闭编辑器

class AnnotationDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AnnotationDelegate(QStringList metaDataList,QObject *parent = 0);

//    创建你编辑时候的控件,双击调用
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

//    使用模型中的数据填充编辑器(此处注释掉是因为,需要QCombobox可以进行编辑,如果重写了该方法,那么在双击编辑时,如果文字不包含在在QCombobox的option中,文字会消失掉)
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;

//    将数据写入到模型中,编辑完成，保存数据到data中(当QCombobox被点击时会被触发)
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

//    设置编辑控件的位置和大小。样式等
    void updateEditorGeometry (QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

//    之前我们写的自定义委托,每次都需要双击某个数据项,才能弹出编辑器,那如何让委托一直呈现在视图显示上呢？步骤如下:
//    重写委托类的paint成员函数
//    在paint()中,通过QApplication::style()->drawControl()来自定义数据显示方式,比如绘制按钮
//    重写委托类的editorEvent成员函数
//    在editorEvent中处理交互事件,比如判断鼠标是否双击,以及更改模型数据等
//    但是实际而言对于QComboBox来说,并没有达到我的预期效果,最后通过QAbstractItemView::openPersistentEditor()实现了
//    详见：mainwidget.cpp中configAnnotationDisplay() 方法,https://stackoverflow.com/questions/5549577
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

//    响应事件 - 鼠标划过、按下
    bool editorEvent ( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index );

signals:

    void markTextInfoUpdate(QString markInfoText,const QModelIndex &index) const;

private:
    QStringList metaDataList;
};

#endif // ANNOTATIONDELEGATE_H
