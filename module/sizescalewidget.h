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
    void initUI();
//    设置当前缩放比例文字信息
    void setSizeScale(QString scale);

private slots:
    void on_enlarge_btn_clicked();

    void on_narrow_btn_clicked();

    void on_adapt_window_btn_clicked();


signals:
    void enlarge();
    void narrow();
    void adaptWindow();

private:
    Ui::SizeScaleWidget *ui;
};

#endif // SIZESCALEWIDGET_H
