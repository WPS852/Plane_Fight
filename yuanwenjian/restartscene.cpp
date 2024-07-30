#include "restartscene.h"
#include<QPainter>
#include<QDebug>
#include"mainscene.h"
#include <QLineEdit>
#include <QCompleter>
#include "startscene.h"
#include "paihangbang.h"
#include "QSound"
restartscene::restartscene(QWidget *parent) : QWidget(parent)
{
    //显示图片
    //frame.load(FRAME_PATH);
    //frame=frame.scaled(GAME_WIDTH+13,GAME_HEIGHT*0.35);
    //设置窗口大小
    this->setFixedSize(GAME_WIDTH+13,GAME_HEIGHT);

    //重新开始按钮
    restartbtn=new startbutton(2);
    restartbtn->setParent(this);
    restartbtn->move(restartbtn->myy+10,restartbtn->myx+10);

    connect(restartbtn,&QPushButton::clicked,[=](){
        //设置点击特效
        restartbtn->zoom1();
        restartbtn->zoom2();
        //重新开始
        QTimer::singleShot(300,this,[=](){
            this->hide();
            emit sendreshow();
        });
    });


    //打开排行榜按钮
    returnbtn=new startbutton(4);
    returnbtn->setParent(this);
    returnbtn->move(returnbtn->myy+10,returnbtn->myx+20);
    connect(returnbtn,&QPushButton::clicked,[=](){
        //设置点击特效
        QSound::play(":/res/ziu_01.wav");
        returnbtn->zoom1();
        returnbtn->zoom2();
        mypaihangbang=new paihangbang();
        mypaihangbang->show();
        mypaihangbang->move(750,300);//将窗口移动到正常的位置
    });
}

void restartscene::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    //画背景图（与游戏开始前的一样）
    painter.drawPixmap(0,mymap.m_map1_posY,mymap.m_map1);
    painter.drawPixmap(0,mymap.m_map2_posY,mymap.m_map2);
    painter.drawPixmap(0,GAME_HEIGHT*0.3,frame);
    //显示文字
    painter.setFont(QFont("黑体",30));
    painter.drawText(0.5*GAME_WIDTH-75-10,0.5*GAME_HEIGHT-15,"游戏结束");
    painter.setFont(QFont("黑体",20));
    painter.drawText(0.5*GAME_WIDTH-45-10,0.5*GAME_HEIGHT+25,"得分："+QString::number(MainScene::recorde));
}
