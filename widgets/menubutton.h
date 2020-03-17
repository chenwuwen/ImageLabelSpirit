#ifndef MEUNBUTTON_H
#define MEUNBUTTON_H

#include <QWidget>
#include <QString>
#include <QtWidgets/QLabel>

class MenuButton : public QWidget
{
    Q_OBJECT
public:


    explicit MenuButton(QWidget *parent = nullptr);

    explicit MenuButton(QString img ,QString name,QWidget *parent = nullptr );

signals:

public slots:

private:
    QLabel *nameLabel;
    QLabel *imgLabel;
    QWidget *menuButtonWidget;
};


#endif // MEUNBUTTON_H
