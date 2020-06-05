#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QWidget>
#include <common/commonutil.h>

namespace Ui {
class ProgressWidget;
}

class ProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressWidget(QWidget *parent = nullptr);
    ~ProgressWidget();
    void setProgressInfo(QString info,int imgCount,int hasMarkCount);

private:
    Ui::ProgressWidget *ui;
};

#endif // PROGRESSWIDGET_H
