#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QFile>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_pushButton_clicked();
    void on_openDirButton_clicked();
    void on_importButton_clicked();

private:
    Ui::MainWidget *ui;

    QStandardItemModel *imgFilesItemModel;
};

#endif // MAINWIDGET_H
