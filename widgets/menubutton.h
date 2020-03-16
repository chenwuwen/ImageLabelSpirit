#ifndef MEUNBUTTON_H
#define MEUNBUTTON_H

#include <QWidget>
#include <QString>

class MenuButton : public QWidget
{
    Q_OBJECT
public:
    explicit MenuButton(QWidget *parent = nullptr);

    explicit MenuButton(QString img ,QString name,QWidget *parent = nullptr );

signals:

public slots:
};

#endif // MEUNBUTTON_H
