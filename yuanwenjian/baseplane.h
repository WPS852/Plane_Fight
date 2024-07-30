#ifndef BASEPLANE_H
#define BASEPLANE_H
#include<QPixmap>

class BasePlane    //抽象类，为所有飞机类的基类
{
public:
    BasePlane();
    //纯虚函数
    virtual void shoot()=0;

    int m_x,m_y;         //坐标
    int m_recorder;      //管理子弹发射的变量
    QRect m_Rect;        //碰撞体积
};

#endif // BASEPLANE_H
