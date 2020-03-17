#include "bform.h"
#include "ui_bform.h"

BForm::BForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BForm)
{
    ui->setupUi(this);
}

BForm::~BForm()
{
    delete ui;
}
