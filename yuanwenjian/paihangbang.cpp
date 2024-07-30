#include "paihangbang.h"
#include "config.h"
#include <QString>
#include "lianbiao.h"
#include <QLabel>
#include <QDebug>
#include<QString>

paihangbang::paihangbang(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(GAME_WIDTH+13,500);
    //设置图标和标题
    this->setWindowIcon(QIcon(GAME_ICON));
    setWindowTitle("排行榜");
    for(int i=0;i<6;i++)
        tab[i].load(TABLE_PATH);
}

void paihangbang::paintEvent(QPaintEvent *ev)
{
    //画出初始背景，与游戏刚开始时的相同
    QPainter painter(this);
    painter.drawPixmap(0,mymap.m_map2_posY-250,mymap.m_map2);
    for(int i=0;i<6;i++)
        painter.drawPixmap(0.5*(GAME_WIDTH-tab[i].width()),70*i+50,tab[i]);

    //设置字为黑色
    painter.setPen(Qt::black);
    //设置字体，大小和文字
    painter.setFont(QFont("黑体",15));
    painter.drawText(90,30,"得分    日期     排名");

    Player* temp = Player::show();
    for(int i=0;i<6;i++)
    {
        if(temp[i].score==0) break;
        //显示分数
        painter.drawText(90,90+70*i,QString::number(temp[i].score));
        //显示时间
        painter.drawText(160,90+70*i,QString::number(temp[i].y));
        painter.drawText(213,90+70*i,"-");
        painter.drawText(230,90+70*i,QString::number(temp[i].m));
        painter.drawText(250,90+70*i,"-");
        painter.drawText(270,90+70*i,QString::number(temp[i].d));
        //显示排名
        painter.drawText(340,90+70*i,QString::number(i+1));
    }

}
