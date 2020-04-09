#ifndef SPLASHWIDGET_H
#define SPLASHWIDGET_H

#include <QWidget>
namespace Ui {
class SplashWidget;
}

//启动页
class SplashWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SplashWidget(QWidget *parent = nullptr);
    ~SplashWidget();

private:
    Ui::SplashWidget *ui;
    QMovie *movie;
    int frameCount;

protected slots:
//    启动到主界面
    void startMainWidget();
    void stopMovieAndStartMainWidget(int);
};

#endif // SPLASHWIDGET_H
