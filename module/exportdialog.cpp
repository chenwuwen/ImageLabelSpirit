#include "exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    setWindowTitle("导出文件");
}

ExportDialog::~ExportDialog()
{
    delete ui;
}
