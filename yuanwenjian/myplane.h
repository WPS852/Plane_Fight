#ifndef MYPLANE_H
#define MYPLANE_H
#include<QPixmap>
#include"bullet.h"
#include"baseplane.h"

class myplane:public BasePlane     //玩家的飞机类
{
public:
    myplane();
    void shoot();          //射击
    void setPosition(int x,int y);    //设置位置
public:
    QPixmap m_Plane;       //加载图片
    bullet m_bullets[BULLET_NUM];

    ///以下变量继承于BasePlane
    //int  m_recorder;
    //int m_x;
    //int m_y;
    //QRect m_Rect;
};

#endif // MYPLANE_H
