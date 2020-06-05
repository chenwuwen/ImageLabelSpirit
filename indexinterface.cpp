#include "indexinterface.h"
#include "ui_indexinterface.h"





//声明一个全局变量,用来表示当前项目的文件地址,其他cpp文件可以引用它,不能使用extern/static修饰
QString CURRENT_PROJECT_FILE_PATH;

IndexInterface::IndexInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexInterface)
{
    ui->setupUi(this);
    resize(1280,720);

//    居中
    int cx, cy;
    cx = (QApplication::desktop()->width() - width()) / 2;
    cy = (QApplication::desktop()->height() - height()) / 2;
    move(cx, cy);

//    配置无边框
    QWidget::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    setWindowIcon(QIcon(":/res/icons/kanyun.png"));
    setWindowTitle("看云图片标注精灵");
    CommonUtil::setQssStyle(":/res/style/index_widget_style.qss",this);
    ui->close_index_widget_btn->setFlat(true);
//    使用Qt内置的图标
    QStyle* style = QApplication::style();
    ui->close_index_widget_btn->setIcon(style->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->header_widget->layout()->setAlignment(Qt::AlignRight);
//    为QListWidget设置大小调整策略
    ui->project_preview_list_widget->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    loadAllProject();

}

IndexInterface::~IndexInterface()
{
    delete ui;
}

void IndexInterface::loadAllProject()
{
    QFileInfoList projects = CommonUtil::getProjectInfoList();
    int projectCount = projects.size();
    qDebug() << QString("查找到[%1]个项目").arg(projectCount);
    for(int i = 0 ; i < projectCount ; i++){
        QFileInfo pjFile = projects.at(i);
        Project project = CommonUtil::readProjectInfo(pjFile.absoluteFilePath());
        qDebug() << "得到反序列化的结果：" << project.projectName << "  " << project.annotationMeta;
        ProjectPreview *projectPreview = new ProjectPreview(project,pjFile.absoluteFilePath());
        QListWidgetItem *item = new QListWidgetItem;

        item->setSizeHint(QSize(30,ui->project_preview_list_widget->width()));
        item->setData(Qt::UserRole,QVariant::fromValue(project));
//        重要：先addItem 然后再setItemWidget否则列表为空
        ui->project_preview_list_widget->addItem(item);
//        设置item的内容是自定义的widget
        ui->project_preview_list_widget->setItemWidget(item,projectPreview);
//        双击Item时,触发双击信号,打开项目槽函数处理
        connect(projectPreview,static_cast<void (ProjectPreview::*) (QString)>(&ProjectPreview::openCurrentProject),this,&IndexInterface::openProject);
//        处理删除项目
        connect(projectPreview,&ProjectPreview::deleteProjectItem,this,&IndexInterface::removeProjectItem);
//        重命名项目
        connect(projectPreview,static_cast<void (ProjectPreview::*) (QString)>(&ProjectPreview::projectNameModify),this,&IndexInterface::renameProject);

    }
}

void IndexInterface::renameProject(QString newProjectName)
{
      QListWidgetItem *currentItem=ui->project_preview_list_widget->currentItem();
      QVariant variant = currentItem->data(Qt::UserRole);
      ProjectInfo info = variant.value<ProjectInfo>();
      info.projectName = newProjectName;
      CommonUtil::saveProjectInfo(info);
}



void IndexInterface::on_create_project_btn_clicked()
{
    createProjectDialog = new CreateProjectDialog(this);
    connect(createProjectDialog,&CreateProjectDialog::createProject,this,&IndexInterface::compileCreateProject);
    int code = createProjectDialog->exec();
    if (code == QDialog::Accepted){
        loadAllProject();
    }

}

void IndexInterface::compileCreateProject(QString projectName, QString imgPath, QString annotationMeta)
{
//    获取当前时间
    QDateTime time = QDateTime::currentDateTime();
//    将当前时间转为时间戳
    uint second = time.toTime_t();
    qDebug() << "新创建的项目信息：" << projectName << "  " << imgPath << "  " << annotationMeta << "  " << QString::number(second);

    Project project;

    project.imgPath = imgPath;
    project.projectName=projectName;
    project.annotationMeta = annotationMeta;
    project.createTime=QString::number(second);
    CommonUtil::saveProjectInfo(project);
}

void IndexInterface::on_close_index_widget_btn_clicked()
{
    this->close();
}

void IndexInterface::openProject(QString project_file_path)
{

    CURRENT_PROJECT_FILE_PATH = project_file_path;
    qDebug() << "双击项目概览,打开项目：" << CURRENT_PROJECT_FILE_PATH;
    MainInterface *mw = new MainInterface;
    mw->show();
    this->close();
}

void IndexInterface::removeProjectItem()
{
    QListWidgetItem *currentItem=ui->project_preview_list_widget->currentItem();
    ui->project_preview_list_widget->removeItemWidget(currentItem);
}
