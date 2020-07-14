#include "annotationcombobox.h"

#define cout qDebug() << "[" <<__FILE__<< " : "<<__LINE__<<"]"

static QString EDIT_STRING = "自定义输入";

AnnotationComboBox::AnnotationComboBox(QWidget *parent) : QComboBox(parent)
{
//    先设置QComboBox为不可编辑
    setEditable(false);

    setStyleSheet("QComboBox QAbstractItemView::item::!enabled {background-color:rgb(238,238,238); } ");

    QComboBox::addItem(QIcon(":/res/icons/edit.png"),EDIT_STRING);
    QComboBox::addItem("预定义分类");

    connect(this,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[=](int currentIndex){
        if (currentIndex == 0){
//              如果点击的允许自定义编辑,则设置为可编辑
            setEditable(true);
//                如果选择的是第一个,则设置索引为-1
//                当QComboBox添加了许多item之后，显示时会默认选中第一个item，如果想默认一个都不选中，即显示为空。就设置setCurrentIndex(-1);
            setCurrentIndex(-1);
            cout << "该下拉框组件已经开启编辑模式";
        }

        if (currentIndex !=0 && currentIndex != -1){
            setEditable(false);
        }
    });
}

void AnnotationComboBox::wheelEvent(QWheelEvent *event)
{
    return;
}

void AnnotationComboBox::showEvent(QShowEvent *e)
{

    QTimer::singleShot(1,this,[=]{

    });
}

void AnnotationComboBox::addItems(const QStringList &texts)
{

    QComboBox::addItems(texts);
//    禁用第2个item
    QVariant disableV(0);
    setItemData(1, disableV, Qt::UserRole - 1);
    setCurrentIndex(-1);
}

void AnnotationComboBox::mousePressEvent(QMouseEvent *e)
{
    QComboBox::mousePressEvent(e);
}
