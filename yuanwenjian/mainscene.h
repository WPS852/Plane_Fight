#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QTimer>
#include <QWidget>
#include"map.h"
#include"myplane.h"
#include"bullet.h"
#include"smallplane.h"
#include<QLabel>
#include"restartscene.h"
#include"middleplane.h"
#include "lianbiao.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    //函数成员
    MainScene(QWidget *parent = nullptr);       //构造函数
    ~MainScene();                               //析构函数
    void initScene();                           //开始游戏时的工作
    void collisiondownrecorde();                //检查玩家是否被敌机子弹打中
    void mouseMoveEvent(QMouseEvent *event);    //鼠标控制飞机位置
    void enemyToScene();                        //小飞机出现
    void enemyToScene2();                       //中飞机出现
    void playGame();                            //开始游戏
    void updatePosition();                      //更新坐标位置，发射子弹等功能
    void paintEvent(QPaintEvent *event);        //画图，更新图片位置
    void collisionDetection();                  //检查玩家是否被敌机撞击
    void updaterecorde();
    bool defeat();                              //检查游戏是否结束
    void reshow();
    void keyPressEvent(QKeyEvent* ev);          //按暂停按钮能够实现暂停

    //数据成员
    int m_recorder;                           //控制小飞机出现频率的变量
    int m_recorder2;                          //控制中飞机出现频率的变量
    static int recorde;                       //分数
    Map m_map;                                //游戏背景图
    myplane *my_plane;                        //玩家的飞机，指针变量
    SmallPlane *m_enemys[ENEMY_NUM];          //小飞机
    MiddlePlane *mid_enemys[ENEMY_NUM];       //中飞机
    QTimer m_Timer;                           //QTimer类对象
    restartscene *restart;                    //重新开始界面
    startbutton *pausebtn;                    //继续游戏按钮

signals:
    void sendreshow();
    void pausegame();
};
#endif // MAINSCENE_H
