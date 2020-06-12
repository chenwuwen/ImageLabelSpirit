#include "projectpreview.h"
#include "ui_projectpreview.h"




ProjectPreview::ProjectPreview(ProjectInfo project,QString projectFilePath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectPreview)
{
    ui->setupUi(this);


    ui->delete_project_btn->setFlat(true);
//    设置项目名称
    ui->project_name->setText(project.projectName);
//    设置项目图片文件夹路径
//    先判断路径是否存在
    QDir dir(project.imgPath);
    if (!dir.exists()){
        qDebug() << "图片文件夹路径不存在";
//        如果图片文件夹路径不存在,则设置QLabel文字颜色为红色
//        但是在这里使用QPalette这种方式不生效。因为该类是作为QListViewWidget的子元素使用的,因此改用Html方式设置
//        见：http://www.qtcn.org/bbs/simple/?t46376.html
//           https://www.cnblogs.com/azbane/p/12609611.html
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);
        ui->project_img_path->setPalette(pe);
        imgPathExist = false;
        ui->project_img_path->setText("<font  color= red>"+project.imgPath+"</font>");
    }else{
        ui->project_img_path->setText(project.imgPath);
    }


    QDateTime time = QDateTime::fromTime_t(project.createTime.toUInt());
//    设置项目日期(日期格式化)
    ui->project_create_date->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    this->projectFilePath = projectFilePath;

    ui->img_label->setPixmap(QPixmap(":/res/icons/funny.png"));
//    创建一个菜单
    QMenu *operationMenu = new QMenu(this);
//    添加Action及对应槽函数,注意槽函数的写法
    operationMenu->addAction(tr("打开"),this,[=](){
        qDebug() << "QToolButton打开项目";
        emit openCurrentProject(projectFilePath);
    })->setCheckable(false);
    operationMenu->addAction(tr("重命名"),this,&ProjectPreview::renameProject)->setCheckable(false);
//    添加一条分割线
    operationMenu->addSeparator();
    QAction *deleteAction = operationMenu->addAction(tr("删除"),this,&ProjectPreview::on_delete_project_btn_clicked);
    deleteAction->setObjectName("delete_project_action");
    deleteAction->setCheckable(false);
//    添加菜单
    ui->operation_project_btn->setMenu(operationMenu);
//    设置弹出模式 InstantPopup即为点击按钮立即弹出菜单
    ui->operation_project_btn->setPopupMode(QToolButton::InstantPopup);
//    控制QToolButton按钮的文字和图标如何显示
    ui->operation_project_btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
//    设置鼠标样式
    setCursor(Qt::PointingHandCursor);

    CommonUtil::setQssStyle(":/res/style/project_preview_style.qss",this);

    ui->delete_project_btn->hide();
    ui->operation_project_btn->hide();

    currentProject = project;
}



ProjectPreview::~ProjectPreview()
{
    delete ui;
}

void ProjectPreview::renameProject()
{
//    对话框标题
    QString dlgTitle = QStringLiteral("项目重命名");
//    对话框Label显示内容
    QString txtLabel=QStringLiteral("请输入新的项目名称：");
//    对话框内输入框的默认内容
    QString defaultInput = currentProject.projectName;
//    输入框的文本内容为正常显示
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
//    输入框的文本内容为密码方式显示
//    QLineEdit::EchoMode echoMode=QLineEdit::Password;
    bool ok=false;

    QInputDialog *inputDialog = new QInputDialog(this);
    inputDialog->setOkButtonText("确定");
    inputDialog->setCancelButtonText("取消");

//    第一个参数parent:父窗口的指针 ,可以为NULL,this[这里为this的话QInputDialog的背景色为黑色]
//    第二个参数title:输入对话框的标题
//    第三个参数label:在输入框上面的提示语句
//    第四个参数mode用于指明这个QLineEdit的输入模式，取值范围是QLineEdit::EchoMode，默认是Normal，也就是正常显示，你也可以声明为password，这样就是密码的输入显示了
//    第五个参数text: QLineEdit的默认字符串
//    第六个参数ok是可选的，如果非NULL，则当用户按下对话框的OK按钮时，这个bool变量会被置为true，可以由这个去判断用户是按下的OK还是Cancel，从而获知这个text是不是有意义；
//    第七个参数flags：用于指定对话框的样式 https://blog.csdn.net/xuebing1995/article/details/96478891
//    第八个参数inputMethodHints：属性只对输入部件有效,输入法使用它来检索有关输入法应如何操作的提示，例如，如果设置了只允许输入数字的标志，则输入法可能会更改其可视组件，以反映只能输入数字 https://blog.csdn.net/LaoYuanPython/article/details/102708898

    QString text = inputDialog->getText(NULL,dlgTitle,txtLabel,echoMode,defaultInput,&ok,Qt::Widget|Qt::FramelessWindowHint,Qt::ImhNone);
    if(ok && !text.isEmpty()){
        if (text != defaultInput){
            qDebug() << "重命名项目名,新项目名称：" << text;
            ui->project_name->setText(text);
            emit projectNameModify(text);
        }
    }

}

void ProjectPreview::mouseDoubleClickEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && imgPathExist){
//        此信号连接到 indexwidget.cpp中的openProject槽函数
        emit openCurrentProject(projectFilePath);
    }

    if (event->button() == Qt::LeftButton && !imgPathExist){
//        此信号连接到 indexwidget.cpp中的openProject槽函数
        emit imgPathNotFound(projectFilePath);
    }

}

void ProjectPreview::enterEvent(QEvent *)
{
    ui->delete_project_btn->show();
    ui->operation_project_btn->show();
}

void ProjectPreview::leaveEvent(QEvent *)
{
    ui->delete_project_btn->hide();
    ui->operation_project_btn->hide();
}

void ProjectPreview::on_delete_project_btn_clicked()
{
    qDebug() << "删除project";
    // 创建一个question弹出对话框，添加两个按钮：Yes和Cancel
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Question, tr("提示"), tr("确定要删除项目吗"), QMessageBox::Yes | QMessageBox::Cancel);

    // 将原本显示“Yes”的按钮改为显示“是”
    msgBox->button(QMessageBox::Yes)->setText("确定");

    // 将原本显示“Cancel”的按钮改为显示“否”
    msgBox->button(QMessageBox::Cancel)->setText("取消");

    // 弹出对话框
    int code = msgBox->exec();

    if (code == QMessageBox::No) return;
    QFile file(projectFilePath);
//    移除项目文件
    file.remove();
//    发送删除项目信号给IndexWidget
    emit deleteProjectItem();
}




