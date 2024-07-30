#include "middleplane.h"
#include "mainscene.h"
#include "QSound"
MiddlePlane::MiddlePlane()
{
    blood=BLOOD;
    Mid_enemy.load(ENEMY_PATH2);          //加载图片
    m_x=0;                                //初始坐标位置（左上角）
    m_y=0;
    outscreen=0;                          //没有离开屏幕
    m_Free=true;                          //暂定free
    m_Speed=ENEMY_SPEED-1;                  //设置速度
    //设置碰撞体积及其位置
    m_Rect.setWidth(0.6*Mid_enemy.width());
    m_Rect.setHeight(0.8*Mid_enemy.height());
    m_Rect.moveTo(m_x+0.2*Mid_enemy.width(),m_y+0.1*Mid_enemy.height());
    m_recorder=80;                        //初始设置为80

    //实现多态的关键步骤②：使指针变量指向对应的变量，之后的函数全用指针调用以实现多态
    for(int i=0;i<5;i++)
        mybullet[0][i]=&bullet0[i];
    for(int i=0;i<5;i++)
        mybullet[1][i]=&bullet1[i];
    for(int i=0;i<5;i++)
        mybullet[2][i]=&bullet2[i];
}

void MiddlePlane::shoot()
{
    m_recorder++;
    if(m_recorder<Bullet_INTERVAL*8){return;}
    m_recorder=0;
    QSound::play(":/res/da_01.wav");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(mybullet[i][j]->m_free)     //如果哪个子弹free了
            {

                mybullet[i][j]->m_free=false;
                mybullet[i][j]->m_x=m_x+Mid_enemy.width()*0.5-4;  //发射
                mybullet[i][j]->m_y=m_y+80;
                break;
            }
        }
    }
}

void MiddlePlane::updatePosition()
{
    //根据分数调整敌机的速度(不能太高)
    if(MainScene::recorde<=300) m_Speed=ENEMY_SPEED+MainScene::recorde/100-2;
    else m_Speed=ENEMY_SPEED;

    if(m_Free){return;}               //如果是free就不调整位置
    m_y+=m_Speed;                     //调整位置
    m_Rect.moveTo(m_x+0.2*Mid_enemy.width(),m_y+0.1*Mid_enemy.height());           //碰撞体积移动
    if(m_y>=GAME_HEIGHT+m_Rect.height())
    {m_Free=true;outscreen++;}
    //若离开屏幕，则使其free且令outscreen=1。
}
