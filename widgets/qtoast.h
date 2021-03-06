﻿#pragma execution_character_set("utf-8")
#ifndef QTOAST_H
#define QTOAST_H

#include <QDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QMovie>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
/*
 * QToast : 仿Android中Toast控件，用于弹出任意Widget，
 *          常见用法如弹出一个文字提示，图片，GIF等，并于特定时间后自动隐藏
 *
 * 类中提供了三个静态函数分别用于显示文本，图片和GIF。如有其他需要可以参照这些静态函数自行修改。
*/

class QToast : public QDialog
{
    Q_OBJECT
public:
    QToast(QWidget *parent = nullptr);
    ~QToast();

    /*
     * SetWidget:设置要展示的Widget窗口，默认为nullptr
    */
    void SetWidget(QWidget *widget);

    /*
     * SetDisplayTime:设置 QToast 的显示时间，超过这个时间，窗口自动隐藏，单位：毫秒
     *
     * 默认为 -1 ，也就是不会自动消失
     *
     * 如果设置了正值的显示时间，隐藏窗口的时候，会自动根据SetAnimation的值来决定是否开启隐藏动画
    */
    void SetDisplayTime(int mSecs);

    /*
     * SetAnimation:显示和隐藏窗口时，是否采用动画，而不是直接显示和消失
     *
     * 默认为 true ，也就是使用动画，显示时，应该调用StartShowAnimation()
    */
    void SetAnimation(bool show);

    /*
     * SetDeleteWhenHide:设置窗口隐藏时是否自动删除QToast,默认为false
     *
     * 这个方法，主要是用于静态函数中的，此时用于不会获取QToast的指针，所以需要自动删除掉
     * 如果用户不是使用静态函数，而是需要自已 new 出一个 QToast 的，则最好不要用这个函数
    */
    void SetDeleteWhenHide(bool deleteWhenHide);

    /*
    * MoveToPercentage:将QToast的中点移动到指定的位置，参数hPer和vPer表示百分比。
    *
    * 如果QToast的parent为一个Widget，那么它的位置是相对于parent widget的
    * 如果QToast的parent为nullptr，那么它的位置是相对于电脑的主屏幕的
    *
    * 如果取值为0~1.0，那么QToast会自动移动到指定的百分比点，如果其中有任意一个设置为负数，
    * 那么，不会自动移动，此时需要用户去调用 QWidget::move()来指定位置。
    *
    * MoveToCenter 即为 MoveToPercentage(0.5,0.5);
    *
    * 默认会调用MoveToPercentage(-1,-1),也就是不开启自动移动
    */
    void MoveToCenter();
    void MoveToPercentage(qreal hPer,qreal vPer);

    /**
     * @brief SetShadow 设置阴影
     */
    void SetShadow();

public slots:
    void StartShowAnimation();
    void StartHideAnimation();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
private:
    void Init();
    void InitAnimation();
    void SetDelaySeconds(int mSecs);
    void MovePostion();

    QWidget            *m_pCentralWidget;
    qreal               m_dHPer,m_dVPer;
    int                 m_nDisplayTimeByMSecs;
    bool                m_bShowAnimation;
    bool                m_bDeleteWhenHide;
//    动画Qt属性的类 (隐藏动画)
    QPropertyAnimation *m_pHideAnimation;
//    动画Qt属性的类 (显示动画)
    QPropertyAnimation *m_pShowAnimation;



public:
    /**
     * @brief ShowText 文字是展示在QLable上的,Qlable是放在QToast上的,使用的是垂直布局, QToast是QDialog的子类
     * @param text 要展示的文字
     * @param displayTimeByMSec 展示时间
     * @param hPercentage 横向位置百分比
     * @param vPercentage  纵向位置百分比
     * @param parent
     */
    static void ShowText(const QString &text,int displayTimeByMSec = 5000,
                         double hPercentage = 0.5,double vPercentage = 0.8,QWidget *parent = nullptr)
    {
        QFont iFont;
        iFont.setPixelSize(20);

        QLabel *pLabel = new QLabel;
        pLabel->setFrameStyle(QFrame::Panel);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setFont(iFont);
//        文字是否换行
        pLabel->setWordWrap(true);
        pLabel->setText(text);

        QString qss = "background-color:rgb(74,64,53);"
                      "border:none;"
                      "color:#ffffff;";

        pLabel->setStyleSheet(qss);


        QToast *iToast = new QToast(parent);
        QFontMetrics metrics(iFont);
//        得到pLabel尺寸 pLabel->maximumWidth() 得到的是QLable的默认最大宽度
        QRect rect = metrics.boundingRect(QRect(0,0,pLabel->maximumWidth(),pLabel->maximumHeight()),
            Qt::AlignCenter|Qt::TextWordWrap,text);

//        根据pLabel的尺寸,重定义iToast的尺寸,在既有文字的基础尺寸上再加上一个值
        iToast->resize(rect.size()+QSize(metrics.width("A"),10));
//        将QLable放到QToast上,也就是QDialog上
        iToast->SetWidget(pLabel);
//        设置阴影
        iToast->SetShadow();
        iToast->SetDisplayTime(displayTimeByMSec);
        iToast->SetDeleteWhenHide(true);
        iToast->MoveToPercentage(hPercentage,vPercentage);
        iToast->StartShowAnimation();
    }

    static void ShowPixmap(const QPixmap &pixmap,int displayTimeByMSec = 5000,
                           double hPercentage = 0.5,double vPercentage = 0.8,QWidget *parent = nullptr)
    {
        if(pixmap.isNull())
        {
            ShowText(u8"pixmap为NULL，无法显示图片!",displayTimeByMSec,hPercentage,vPercentage,parent);
            return;
        }

        QLabel *pLabel = new QLabel;
        pLabel->setFrameStyle(QFrame::Panel);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setPixmap(pixmap);


        QToast *iToast = new QToast(parent);
        iToast->resize(pixmap.size());

        iToast->SetWidget(pLabel);
        iToast->SetDisplayTime(displayTimeByMSec);
        iToast->SetDeleteWhenHide(true);
        iToast->MoveToPercentage(hPercentage,vPercentage);
        iToast->StartShowAnimation();
    }

    static void ShowMoive(QMovie *movie,double hPercentage = 0.5,double vPercentage = 0.8,
                          QWidget *parent = nullptr)
    {
        if((movie == nullptr) || !movie->isValid())
        {
            ShowText(u8"movie为nullptr或无效，无法显示Gif!",5000,hPercentage,vPercentage,parent);
            return;
        }

        QLabel *pLabel = new QLabel;
        pLabel->setFrameStyle(QFrame::Panel);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setMovie(movie);


        QToast *iToast = new QToast(parent);
        iToast->resize(QPixmap(movie->fileName()).size());
        iToast->SetWidget(pLabel);
        iToast->SetDisplayTime(-1);
        iToast->SetDeleteWhenHide(true);
        iToast->MoveToPercentage(hPercentage,vPercentage);
        iToast->StartShowAnimation();
        movie->start();

        if(iToast->m_bShowAnimation)
        {
            QObject::connect(movie,SIGNAL(finished()),iToast,SLOT(StartHideAnimation()));
        }
        else
        {
            QObject::connect(movie,SIGNAL(finished()),iToast,SLOT(hide()));
        }
    }
};

#endif // QTOAST_H
