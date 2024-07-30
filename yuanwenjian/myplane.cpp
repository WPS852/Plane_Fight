#include "myplane.h"
#include"config.h"
#include"mainscene.h"
#include "QSound"
#include "media.h"
extern media *m;
myplane::myplane()
{
    m_Plane.load(MY_PATH);   //加载图片

    for(int i=0;i<BULLET_NUM;i++)
        m_bullets[i].m_bullet.load(MY_BULLET_PATH);

    //设置初始位置，即最下面居中的位置
    m_x=GAME_WIDTH*0.5-m_Plane.width()*0.5;
    m_y=GAME_HEIGHT-m_Plane.height();
    //设置碰撞体积大小及其位置
    m_Rect.setWidth(0.3*m_Plane.width());
    m_Rect.setHeight(0.3*m_Plane.height());
    m_Rect.moveTo(m_x+0.35*m_Plane.width(),m_y+0.5*m_Plane.width());
    m_recorder=0;
}

void myplane::setPosition(int x, int y)
{
    m_x=x;
    m_y=y;
    m_Rect.moveTo(m_x+0.35*m_Plane.width(),m_y+0.5*m_Plane.width());
}

void myplane::shoot()
{
    m_recorder++;
    //射击速度与得分和Bullet_INTERVAL都有关
    int a;//防止射击速度过快
    if(MainScene::recorde<=50) a=MainScene::recorde/5;
    else if(MainScene::recorde<=500) a=7;
    else a=9;

    if(m_recorder<Bullet_INTERVAL-a){return;}
    m_recorder=0;
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_bullets[i].m_free)      //与敌机发射子弹同理
        {
            QSound::play(":/res/ziu_01.wav");

            m_bullets[i].m_free=false;
            m_bullets[i].m_x=m_x+m_Plane.width()*0.5-9;
            m_bullets[i].m_y=m_y-8;
            break;
        }
    }

}
