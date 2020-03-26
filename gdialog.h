#ifndef GDIALOG_H
#define GDIALOG_H

#include <QDialog>

namespace Ui {
class GDialog;
}

class GDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GDialog(QWidget *parent = nullptr);
    ~GDialog();

private:
    Ui::GDialog *ui;
};

#endif // GDIALOG_H
