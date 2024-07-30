#include "leftbullet.h"

leftbullet::leftbullet():bullet()
{}

void leftbullet::updatePosition2(int recorde)  //移动敌机的（左）子弹
{
    if(m_free){return;}         //如果是free的子弹，就不调整位置

    if(recorde<=200) m_y+=m_speed;    //子弹向下移动
    else if(recorde<=300) m_y+=m_speed+1;
    else m_y+=m_speed+2;

    m_x-=2;
    m_Rect.moveTo(m_x,m_y);     //碰撞体积移动
    if(m_y>=GAME_HEIGHT)
        {m_free=true;}
    //如果子弹顶部离开窗口，就使其free
}
