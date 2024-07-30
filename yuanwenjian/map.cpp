#include "map.h"
#include"config.h"
Map::Map()
{
    //加载图片
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);
    m_map1_posY=-852;     //852为背景图片的大小
    m_map2_posY=0;
    m_scroll_speed=MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    //实现动画播放
    m_map1_posY+=  m_scroll_speed;
    if(m_map1_posY>=0){m_map1_posY=-852;}
    m_map2_posY+= m_scroll_speed;
    if(m_map2_posY>=852){m_map2_posY=0;}
}
