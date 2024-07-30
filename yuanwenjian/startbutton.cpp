#include "startbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include "QSound"
#include "media.h"
startbutton::startbutton(int btntype)
{
    if(btntype==1)   //主菜单界面的按钮
    {
        //设置大小
        QSize mysize(150,100);
        //加载按钮图片
        mystartbutton.load(START_BUTTON_PATH);
        //保证图片缩放正常（保持宽高比）
        mystartbutton=mystartbutton.scaled(mysize,Qt::KeepAspectRatio);
        //设置按钮出现的位置
        myx=GAME_HEIGHT*0.6;
        myy=GAME_WIDTH*0.5-0.5*mystartbutton.width();
        this->setIcon(mystartbutton);
        //设置按钮图片的大小
        this->setIconSize(QSize(mystartbutton.width(),mystartbutton.height()));
        //这个是按钮点击有反应的范围的大小
        //this->setFixedSize(QSize(0.61*mystartbutton.width(),0.33*mystartbutton.height()));
        this->setFixedSize(QSize(mystartbutton.width(),mystartbutton.height()));
        //设置无边界
        this->setStyleSheet("QPushButton{border:0px;}");
    }

    else if(btntype==2)    //重新开始的按钮
    {
        QSize mysize(50,50);
        mystartbutton.load(RESTART_BUTTON_PATH);
        mystartbutton=mystartbutton.scaled(mysize,Qt::KeepAspectRatio);
        myx=GAME_HEIGHT*0.53;
        myy=GAME_WIDTH*0.5-0.5*mystartbutton.width();
        this->setIcon(mystartbutton);
        this->setIconSize(QSize(mystartbutton.width(),mystartbutton.height()));
        this->setFixedSize(QSize(mystartbutton.width(),mystartbutton.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
    }

   else if(btntype==3)    //（暂停时会出现的）继续游戏按钮
    {
        QSize mysize(80,80);
        mystartbutton.load(CONTINUE_PATH);
        mystartbutton=mystartbutton.scaled(mysize,Qt::KeepAspectRatio);
        myx=GAME_HEIGHT*0.53;
        myy=GAME_WIDTH*0.5-0.5*mystartbutton.width();
        this->setIcon(mystartbutton);
        this->setIconSize(QSize(mystartbutton.width(),mystartbutton.height()));
        this->setFixedSize(QSize(mystartbutton.width(),mystartbutton.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
    }
    else if(btntype==4)   //主菜单界面的排行榜按钮
    {
        //设置大小
        QSize mysize(150,100);
        //加载按钮图片
        mystartbutton2.load(START_BUTTON_PATH2);
        //保证图片缩放正常（保持宽高比）
        mystartbutton2=mystartbutton2.scaled(mysize,Qt::KeepAspectRatio);
        //设置按钮出现的位置
        myx=GAME_HEIGHT*0.6;
        myy=GAME_WIDTH*0.5-0.5*mystartbutton2.width();
        this->setIcon(mystartbutton2);
        //设置按钮图片的大小
        this->setIconSize(QSize(mystartbutton2.width(),mystartbutton2.height()));
        //这个是按钮点击有反应的范围的大小
        this->setFixedSize(QSize(mystartbutton2.width(),mystartbutton2.height()));
        //设置无边界
        this->setStyleSheet("QPushButton{border:0px;}");
    }
}

void startbutton::zoom1()   //向下运动
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->myy+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
    QSound::play(":/res/di_01.wav");
};

void startbutton::zoom2()      //向上运动
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
    //extern media *m;
    //m->mediaStop1();
};

void startbutton::zoom3()   //向下运动
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->myy+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
};

void startbutton::zoom4()      //向上运动
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
    QSound::play(":/res/di_01.wav");
};

