#ifndef SIZESCALEWIDGET_H
#define SIZESCALEWIDGET_H

#include <QWidget>
#include <common/fontawesomeicons.h>
#include <common/commonutil.h>

namespace Ui {
class SizeScaleWidget;
}

class SizeScaleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SizeScaleWidget(QWidget *parent = nullptr);
    ~SizeScaleWidget();
    void initButton();
//    设置当前缩放比例文字信息
    void setSizeScale(QString scale);

private slots:
    void on_enlarge_btn_clicked();

    void on_narrow_btn_clicked();

    void on_adapt_window_btn_clicked();


signals:
//    图片放大信号
    void enlarge();
//    图片缩小信号
    void narrow();
//    图片适配窗口信号
    void adaptWindow();

private:
    Ui::SizeScaleWidget *ui;
};

#endif // SIZESCALEWIDGET_H
