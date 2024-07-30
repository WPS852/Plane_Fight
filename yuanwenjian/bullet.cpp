#include "bullet.h"

bullet::bullet()  //构造函数
{
    m_bullet.load(BULLET_PATH);        //加载图片
    m_x=GAME_WIDTH*0.5-m_bullet.width()*0.5;     //x坐标，中间偏左
    m_y=GAME_HEIGHT;            //y坐标，顶部
    m_free=true;                //先暂定为free（未发射状态）
    m_speed=BULLET_SPEED;       //设置子弹速度
    //设置碰撞体积的大小和位置
    m_Rect.setWidth(m_bullet.width());
    m_Rect.setHeight(m_bullet.height());
    m_Rect.moveTo(m_x,m_y);
}

void bullet::updatePosition()     //移动玩家的子弹
{
    if(m_free){return;}           //如果是free的子弹，就不调整位置
    m_y-=m_speed;                 //每次调整位置时，子弹（的图片）向上移动
    m_Rect.moveTo(m_x,m_y);       //碰撞体积也随即移动
    if(m_y<=-m_Rect.height())
        {m_free=true;}
    //如果子弹的底部离开窗口，就使其free
}
void bullet::updatePosition2(int recorde)  //移动敌机的（中）子弹
{
    if(m_free){return;}         //如果是free的子弹，就不调整位置

    if(recorde<=200) m_y+=m_speed;          //子弹向下移动
    else if(recorde<=300) m_y+=m_speed+1;
    else m_y+=m_speed+2;

    m_Rect.moveTo(m_x,m_y);     //碰撞体积移动
    if(m_y>=GAME_HEIGHT)
        {m_free=true;}
    //如果子弹顶部离开窗口，就使其free
}
