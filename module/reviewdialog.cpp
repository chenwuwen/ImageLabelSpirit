#include "reviewdialog.h"
#include "ui_reviewdialog.h"



ReviewDialog::ReviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviewDialog)
{
    ui->setupUi(this);
    resize(parent->width() * 0.6,parent->height() * 0.6);
//    配置无边框
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setWindowTitle("查看标注结果");
    CommonUtil::setQssStyle(":/res/style/review_dialog_style.qss",this);

    ui->review_dialog_close_btn->setFlat(true);
    ui->review_dialog_export_btn->setFlat(true);

//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->review_dialog_close_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));

    tableItemModel = new QStandardItemModel;
//    默认显示行头，如果你觉得不美观的话，我们可以将隐藏
    ui->review_table->verticalHeader()->hide();

//    设置选中时为整行选中
   ui->review_table->setSelectionBehavior(QAbstractItemView::SelectRows);
//    设置表格的单元为只读属性，即不能编辑
   ui->review_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
//   表头信息显示水平居左垂直居中
   ui->review_table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);
//   隐藏网格
   ui->review_table->setShowGrid(false);
//   选择整行
   ui->review_table->setSelectionBehavior(QAbstractItemView::SelectRows);
//   奇偶行区分颜色，同时还需要设置qss
   ui->review_table->setAlternatingRowColors(true);
//   列宽随窗口大小改变而改变，每列平均分配，充满整个表，但是此时列宽不能拖动进行改变
   ui->review_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//   设置不换行
   ui->review_table->setWordWrap(false);

   ui->review_table->setModel(tableItemModel);

}

ReviewDialog::~ReviewDialog()
{
    delete ui;
}



void ReviewDialog::setMarkInfoTable(QMap<QString,QList<RectMetaInfo>> markCollection)
{
    this->collection = markCollection;
//    设置表头
    QStringList labels = QObject::trUtf8("文件地址,标注数量,时间").simplified().split(",");
    tableItemModel->setHorizontalHeaderLabels(labels);

    foreach(const QString key,markCollection.keys()){
        QList<QStandardItem *> items;
        QStandardItem *column1 = new QStandardItem(key);
//        这里需要注意QStandardItem有多个构造函数,其中有一个构造函数可以接受一个int类型的值,因此这里使用QString::number()方法来将数字转换为QString类型
        QStandardItem *column2 = new QStandardItem(QString::number(markCollection[key].size()));
        QStandardItem *column3 = new QStandardItem("2020-01-01");
        items << column1 << column2 << column3 ;
        tableItemModel->appendRow(items);
    }

    QString info = QString("共%1条数据").arg(markCollection.keys().size());
    ui->total_value_label->setText(info);

}

void ReviewDialog::setExportLocalPath(QString localPath)
{
    this->localPath = localPath;
}

void ReviewDialog::on_review_dialog_export_btn_clicked()
{
//    this->close();
//    accept()方法也是关闭窗口的方法,但是返回值不同,这样父类就知道是哪个按钮点击的关闭了,从而做出对应操作
    accept();
}

void ReviewDialog::on_review_dialog_close_btn_clicked()
{
//    this->close();
//    reject()方法也是关闭窗口的方法,但是返回值不同,这样父类就知道是哪个按钮点击的关闭了,从而做出对应操作
    this->reject();
}
