#ifndef ENEMYOLANE_H
#define ENEMYOLANE_H

#include"bullet.h"
#include<QPixmap>
#include"baseplane.h"

class SmallPlane:public BasePlane   //敌机类
{
public:
    SmallPlane();               //构造函数
    void updatePosition();      //更新位置
    void shoot();               //发射子弹函数
public:
    QPixmap m_enemy;            //加载图片
    bool m_Free;                //是否free
    int m_Speed;                //速度，定义为每次更新位置时敌机的移动距离
    int outscreen;              //是否已经出屏幕
    bullet mybullet[3];         //三发子弹，保证不会多用子弹

    ///以下变量继承于BasePlane
    //int  m_recorder;
    //int m_x;
    //int m_y;
    //QRect m_Rect;
};

#endif // ENEMYOLANE_H
