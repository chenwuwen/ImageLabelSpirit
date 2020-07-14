#pragma execution_character_set("utf-8")
#ifndef ANNOTATIONCOMBOBOX_H
#define ANNOTATIONCOMBOBOX_H

#include <QComboBox>
#include <QDebug>
#include <QTimer>

/**
 * 自定义QComboBox,目的是禁用鼠标滚轮
 * https://blog.csdn.net/weixin_43935474/article/details/93166390
 * @brief The AnnotationComboBox class
 */
class AnnotationComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit AnnotationComboBox(QWidget *parent = nullptr);
//    重写QComboBox添加Items方法
    void addItems(const QStringList &texts);

private:
    void wheelEvent(QWheelEvent *event);



protected:
//    添加鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *e);
    void showEvent(QShowEvent *e);
signals:

public slots:
};

#endif // ANNOTATIONCOMBOBOX_H
