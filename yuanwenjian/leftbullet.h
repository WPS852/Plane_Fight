#ifndef LEFTBULLET_H
#define LEFTBULLET_H
#include "bullet.h"


class leftbullet: public bullet
{
public:
    leftbullet();
    void updatePosition2(int recorde);     //更新敌机子弹的位置（碰撞体积和坐标）

    ///以下变量继承于bullet
    //QPixmap m_bullet;
    //int m_x;
    //int m_y;
    //int m_speed;
    //bool m_free;
    //QRect m_Rect;
};

#endif // LEFTBULLET_H
