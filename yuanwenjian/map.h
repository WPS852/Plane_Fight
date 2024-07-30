#ifndef MAP_H
#define MAP_H
#include<QPixmap>

class Map
{
public:
    Map();                //构造函数
    void mapPosition();   //更新图片的位置
public:
    //通过两张图堆叠并移动实现背景动画的播放
    QPixmap m_map1;
    QPixmap m_map2;
    int m_map1_posY;
    int m_map2_posY;
    int m_scroll_speed;     //动画速度，定义为每次更新位置时图片的位移
};

#endif // MAP_H
