#include "gdialog.h"
#include "ui_gdialog.h"

GDialog::GDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GDialog)
{
    ui->setupUi(this);
}

GDialog::~GDialog()
{
    delete ui;
}
