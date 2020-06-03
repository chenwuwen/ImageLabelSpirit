#ifndef ANNOTATIONCOMBOBOX_H
#define ANNOTATIONCOMBOBOX_H

#include <QComboBox>


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

private:
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
};

#endif // ANNOTATIONCOMBOBOX_H
