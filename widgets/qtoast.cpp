#include "qtoast.h"

QToast::QToast(QWidget *parent)
    :QDialog (parent)
{
    m_pCentralWidget = nullptr;
    m_pHideAnimation = nullptr;
    m_pShowAnimation = nullptr;
    m_bShowAnimation = true;
    m_bDeleteWhenHide = false;
    m_nDisplayTimeByMSecs = -1;
    m_dHPer = -1;
    m_dVPer = -1;

    Init();
    InitAnimation();
}

QToast::~QToast()
{
    if(m_pHideAnimation)
        m_pHideAnimation->deleteLater();
    if(m_pShowAnimation)
        m_pShowAnimation->deleteLater();
    if(m_pCentralWidget)
    {
        m_pCentralWidget->setParent(nullptr);
        m_pCentralWidget->deleteLater();
    }
}

void QToast::SetWidget(QWidget *widget)
{
    if(nullptr == widget)
        return;

    if(m_pCentralWidget)
    {
        m_pCentralWidget->setParent(nullptr);
        m_pCentralWidget->deleteLater();
    }

    QVBoxLayout *iMainLayout = new QVBoxLayout;
    iMainLayout->setMargin(0);
    iMainLayout->setSpacing(0);

    m_pCentralWidget = widget;
    iMainLayout->addWidget(m_pCentralWidget);

    this->setLayout(iMainLayout);
}

void QToast::SetDisplayTime(int mSecs)
{
    m_nDisplayTimeByMSecs = mSecs;
}

void QToast::SetAnimation(bool show)
{
    m_bShowAnimation = show;
}

void QToast::SetDeleteWhenHide(bool deleteWhenHide)
{
    m_bDeleteWhenHide = deleteWhenHide;
}

void QToast::MoveToCenter()
{
    m_dHPer = 0.5;
    m_dVPer = 0.5;
}

void QToast::MoveToPercentage(qreal hPer, qreal vPer)
{
    m_dHPer = (hPer < 0) ? -1 : ((hPer > 1.0) ? 1.0 : hPer);
    m_dVPer = (vPer < 0) ? -1 : ((vPer > 1.0) ? 1.0 : vPer);
}

void QToast::SetShadow()
{
//        实例阴影shadow
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//        设置阴影距离
        shadow->setOffset(0,0);
//        设置阴影颜色
        shadow->setColor(QColor("#444444"));
//        设置阴影圆角
        shadow->setBlurRadius(30);
//        给嵌套QWidget设置阴影
        this->setGraphicsEffect(shadow);
//        布局器设置边距(此步很重要, 设置宽度为阴影的宽度)
        this->layout()->setMargin(2);
}

void QToast::Init()
{
    if(nullptr == this->parentWidget())
    {
       this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    }
    else
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
    }

    this->setAttribute(Qt::WA_AlwaysStackOnTop,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void QToast::InitAnimation()
{
//    该类用于图形元素的透明效果，主要函数是setOpacity(qreal opacity)，用于设置透明度，参数值在0和1.0之间。
//    也可以设置部分透明效果，需要调用的函数是setOpacityMask (QBrush mask)
    QGraphicsOpacityEffect *pOpacityEffect = new QGraphicsOpacityEffect(this);
    pOpacityEffect->setOpacity(0.0);
    this->setGraphicsEffect(pOpacityEffect);

//    隐藏动画设置
    m_pHideAnimation = new QPropertyAnimation(pOpacityEffect, "opacity",this);
    m_pHideAnimation->setEasingCurve(QEasingCurve::Linear);
    m_pHideAnimation->setDuration(1200);
    m_pHideAnimation->setEndValue(0);

//    显示动画设置
    m_pShowAnimation = new QPropertyAnimation(pOpacityEffect, "opacity",this);
    m_pShowAnimation->setEasingCurve(QEasingCurve::Linear);
    m_pShowAnimation->setDuration(1200);
    m_pShowAnimation->setEndValue(1.0);

//    老版本的槽函数
//    connect(m_pHideAnimation,SIGNAL(finished()),this,SLOT(hide()));
//    新版本槽函数 隐藏动画完毕后(实际上是透明度变为完全透明) 隐藏QDialog
    connect(m_pHideAnimation,&QPropertyAnimation::finished,this,&QToast::hide);
}

void QToast::SetDelaySeconds(int mSecs)
{
    if(mSecs > 0)
    {
        if(m_bShowAnimation)
        {
            QTimer::singleShot(mSecs,this,SLOT(StartHideAnimation()));
        }
        else
        {
            QTimer::singleShot(mSecs,this,SLOT(hide()));
        }
    }
}

void QToast::MovePostion()
{
    qreal hPer = m_dHPer;
    qreal vPer = m_dVPer;

    if(hPer == -1 || vPer == -1)
        return;

    int pWidth,pHeight;
    QWidget *parentWidget = this->parentWidget();
    if(nullptr != parentWidget)
    {
        pWidth = this->parentWidget()->width();
        pHeight = this->parentWidget()->height();
    }
    else
    {
        pWidth = QApplication::primaryScreen()->size().width();
        pHeight = QApplication::primaryScreen()->size().height();
    }

    this->move(pWidth*hPer - this->width()*0.5,pHeight*vPer - this->height()*0.5);
}

void QToast::StartShowAnimation()
{
    this->setVisible(true);
    m_pShowAnimation->start();
}

void QToast::StartHideAnimation()
{
    m_pHideAnimation->start();
}

void QToast::showEvent(QShowEvent *event)
{
    MovePostion();
    QDialog::showEvent(event);
    this->SetDelaySeconds(m_nDisplayTimeByMSecs);
}

void QToast::hideEvent(QHideEvent *event)
{
    QDialog::hideEvent(event);
    if(m_bDeleteWhenHide)
    {
        this->deleteLater();
    }
}
