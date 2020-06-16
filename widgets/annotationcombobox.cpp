#include "annotationcombobox.h"

#define cout qDebug() << "[" <<__FILE__<< " : "<<__LINE__<<"]"

AnnotationComboBox::AnnotationComboBox(QWidget *parent) : QComboBox(parent)
{
//    先设置QComboBox为不可编辑
    setEditable(false);
//    默认填充第3个选项
    setCurrentIndex(2);

    setStyleSheet("QComboBox QAbstractItemView::item::!enabled {background-color:rgb(238,238,238); } ");

    connect(this,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[=](int currentIndex){
        if (currentIndex == 0){
//            如果点击的允许自定义编辑,则设置为可编辑
            setEditable(true);
            setCurrentText("");
            cout << "该下拉框组件已经开启编辑模式";
        }
    });
}

void AnnotationComboBox::wheelEvent(QWheelEvent *event)
{
    return;
}

void AnnotationComboBox::addItems(const QStringList &texts)
{
    QComboBox::addItem(QIcon(":/res/icons/edit.png"),"自定义输入");
    QComboBox::addItem("预定义分类");
    QComboBox::addItems(texts);
//    禁用第2个item
    QVariant disableV(0);
    setItemData(1, disableV, Qt::UserRole - 1);


}

//void AnnotationComboBox::mousePressEvent(QMouseEvent *e)
//{

//}
