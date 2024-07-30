#ifndef MIDDLEPLANE_H
#define MIDDLEPLANE_H

#include"bullet.h"
#include"leftbullet.h"
#include"rightbullet.h"
#include"smallplane.h"
#include<QPixmap>
#include<QVariant>
#include"baseplane.h"

class MiddlePlane:public BasePlane    //敌机（中型）类
{
public:
    MiddlePlane();
    void updatePosition();      //更新位置
    void shoot();               //发射子弹函数
public:
    QPixmap Mid_enemy;        //加载图片
    bool m_Free;                //是否free
    int m_Speed;                //速度，定义为每次更新位置时敌机的移动距离
    int outscreen;              //是否已经出屏幕
    int blood;                  //血量

    //第一个中括号里0,1,2分别表示左子弹，中子弹，右子弹，每个分配五发
    bullet* mybullet[3][5];  //实现多态，设指针变量
    bullet bullet1[5];            //中子弹
    leftbullet bullet0[5];        //左子弹
    rightbullet bullet2[5];       //右子弹

    ///以下变量继承于BasePlane
    //int  m_recorder;
    //int m_x;
    //int m_y;
    //QRect m_Rect;
};

#endif // MIDDLEPLANE_H
