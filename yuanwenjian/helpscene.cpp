#include "helpscene.h"
#include<QPainter>
#include<QFont>
#include<QMouseEvent>
#include "QSound"
#include "media.h"
helpscene::helpscene(QWidget *parent) : QWidget(parent)
{
    //设置窗口大小和图标
    this->setFixedSize(GAME_WIDTH+13,GAME_HEIGHT);
    this->setWindowIcon(QIcon(GAME_ICON));
}

void helpscene::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    //初始两张图片的位置，与游戏刚开始时相同
    painter.drawPixmap(0,mymap.m_map1_posY,mymap.m_map1);
    painter.drawPixmap(0,mymap.m_map2_posY,mymap.m_map2);
    //设置字为黑色
    painter.setPen(Qt::black);
    //设置字体，大小和文字
    painter.setFont(QFont("华文行楷",30));
    painter.drawText(GAME_WIDTH*0.4,GAME_HEIGHT*0.1,"帮助");
    painter.setFont(QFont("华文行楷",15));
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.2,"1.鼠标按住飞机移动，飞机自动发出子弹");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.24,"  射击敌机");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.32,"2.每击落一架敌机，得分+1");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.40,"3.每未能击落一架敌机，得分-2");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.48,"4.被敌机子弹击中，得分-1");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.56,"5.点击ESC按钮可以暂停游戏，再次点击");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.60,"  ESC或点击继续按钮游戏继续");
    painter.drawText(GAME_WIDTH*0.01,GAME_HEIGHT*0.68,"6.随着得分增加，难度会上升");
    painter.drawText(GAME_WIDTH*0.45,GAME_HEIGHT*0.98,"单击鼠标左键以继续...");

}

void helpscene::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        extern media *m;
        m->mediaStop1();
        m->mediaPlay2();
        emit sendend();//发送信号
    }

}
