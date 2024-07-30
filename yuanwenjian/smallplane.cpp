#include "smallplane.h"
#include"config.h"
#include"mainscene.h"
SmallPlane::SmallPlane()
{
    m_enemy.load(ENEMY_PATH);             //加载图片
    m_x=0;                                //初始坐标位置（左上角）
    m_y=0;
    outscreen=0;                          //没有离开屏幕
    m_Free=true;                          //暂定free
    m_Speed=ENEMY_SPEED;                  //设置速度
    //设置碰撞体积及其位置
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_x,m_y);
    m_recorder=80;                        //初始设置为80
}
void SmallPlane::updatePosition()
{
    //根据分数调整敌机的速度(不能太高)
    if(MainScene::recorde<=300) m_Speed=ENEMY_SPEED+MainScene::recorde/100-1;
    else m_Speed=ENEMY_SPEED+1;

    if(m_Free){return;}               //如果是free就不调整位置
    m_y+=m_Speed;                     //调整位置
    m_Rect.moveTo(m_x,m_y);           //碰撞体积移动
    if(m_y>=GAME_HEIGHT+m_Rect.height())
    {m_Free=true;outscreen++;}
    //若离开屏幕，则使其free且令outscreen=1。
}
void SmallPlane::shoot()
{
    m_recorder++;
    if(m_recorder<Bullet_INTERVAL*8){return;}
    m_recorder=0;
    for(int i=0;i<3;i++)
    {
        if(mybullet[i].m_free)     //如果哪个子弹free了
        {
            mybullet[i].m_free=false;
            mybullet[i].m_x=m_x+m_Rect.width()*0.5-5;  //发射
            mybullet[i].m_y=m_y+30;
            break;
        }
    }
}
