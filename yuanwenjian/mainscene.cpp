#include "mainscene.h"
#include"config.h"
#include<QIcon>
#include<QPainter>
#include<QMouseEvent>
#include<ctime>
#include<QLabel>
#include<QColor>
#include "QSound"
#include "media.h"
#include "paihangbang.h"
#include <QLineEdit>
int MainScene::recorde=0; //游戏得分
extern media *m;

MainScene::MainScene(QWidget *parent): QWidget(parent)
{
    initScene();
    playGame();
}

MainScene::~MainScene()
{}

void MainScene::initScene()
{
    //设置大小，标题，图标
    setFixedSize(GAME_WIDTH+13,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_ICON));
    //游戏速度
    m_Timer.setInterval(GAME_RATE);
    m_recorder=0;
    //初始分数为0
    recorde=0;

    //设置随机数种子
    srand((unsigned int)time(NULL));

    //设置继续游戏按钮
    pausebtn=new startbutton(3);
    pausebtn->setParent(this);
    pausebtn->move(pausebtn->myy,pausebtn->myx);
    pausebtn->hide();
    connect(pausebtn,&QPushButton::clicked,[=](){
        //设置点击动画
         pausebtn->zoom1();
         pausebtn->zoom2();
         QTimer::singleShot(200,this,[=](){
            //设置点击事件：再次隐藏按钮，继续游戏
            pausebtn->hide();
            m_Timer.start();

         });

     });

    //定义我的飞机（myplane）
    my_plane=new myplane();
    //定义小敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        m_enemys[i]=new SmallPlane();
    }
    //定义中飞机
    for(int i=0;i<ENEMY_NUM2;i++)
    {
        mid_enemys[i]=new MiddlePlane();
    }
}

void MainScene::playGame()
{
    m_Timer.start();         //开始

    connect(&m_Timer,&QTimer::timeout,[=](){
        enemyToScene();
        if(recorde>=30)enemyToScene2();
        updatePosition();
        update();
        collisionDetection();
        collisiondownrecorde();
        if(defeat())
        {
            m_Timer.stop();    //停止
            QTimer::singleShot(2000,this,[=](){
                restart=new restartscene();  //出现重新开始界面
                this->hide();
                //移动窗口到正常的位置
                restart->show();
                restart->move(750,50);


                Player::addplayers(recorde);

                connect(restart,&restartscene::sendreshow,[=](){
                this->hide();
                emit sendreshow();
                });

            });
        }
    });
}

void MainScene::updatePosition()
{
    m_map.mapPosition();       //更新图片的位置
    my_plane->shoot();         //玩家飞机射击

    //检查所有的玩家子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果这个子弹没有free，则更新坐标位置（坐标和碰撞体积）
        if(!my_plane->m_bullets[i].m_free)
        {
            my_plane->m_bullets[i].updatePosition();
        }
    }

    //检查所有的小飞机
    for(int i = 0 ; i< ENEMY_NUM;i++)
       {
           //非free敌机，更新坐标位置并射击（坐标和碰撞体积）
          if(m_enemys[i]->m_Free == false)
          {
              m_enemys[i]->updatePosition();
              m_enemys[i]->shoot();
              //检查每个敌机的所有子弹，不free则更新坐标（坐标和碰撞体积）
              for(int j=0;j<3;j++)
              {
                 if(! m_enemys[i]->mybullet[j].m_free)
                 {
                      m_enemys[i]->mybullet[j].updatePosition2(recorde);
                 }
              }
              //如果敌机离开了屏幕（即没有打到），扣分。
             if( m_enemys[i]->outscreen>0)
             {
                 if(recorde>=2)
                 {
                     recorde-=2;
                     m_enemys[i]->outscreen=0;
                 }
                else
                 { m_enemys[i]->outscreen=0;}
              }
          }
       }

    //检查所有的中飞机
    for(int i = 0 ; i< ENEMY_NUM2;i++)
       {
          //非free敌机，更新坐标位置并射击（坐标和碰撞体积）
          if(mid_enemys[i]->m_Free == false)
          {
              mid_enemys[i]->updatePosition();
              mid_enemys[i]->shoot();
              //检查每个敌机的所有子弹，不free则更新坐标（坐标和碰撞体积）
              for(int j=0;j<3;j++)
              {
                  for(int k=0;k<5;k++)
                  {
                      if(! mid_enemys[i]->mybullet[j][k]->m_free)
                      {
                           /*if(j==1)*/
                          ///实现多态的重要步骤③：指针直接调用函数
                          mid_enemys[i]->mybullet[j][k]->updatePosition2(recorde);
                           //else if(j==0) mid_enemys[i]->mybullet[j][k]->leftPosition(recorde);
                           //else if(j==2) mid_enemys[i]->mybullet[j][k]->rightPosition(recorde);
                          ///这三行注释是实现多态之前的码
                      }
                  }
              }
              //如果敌机离开了屏幕（即没有打到），扣分。
             if( mid_enemys[i]->outscreen>0)
             {
                 if(recorde>=2)
                 {
                     recorde-=2;
                     mid_enemys[i]->outscreen=0;
                 }
                else
                 { mid_enemys[i]->outscreen=0;}
              }
          }
       }
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setFont(QFont("黑体",15));
    //画背景图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);
    //画玩家飞机
    painter.drawPixmap(my_plane->m_x,my_plane->m_y,my_plane->m_Plane);
    //游戏左上角的计分文字
    QString recstring("得分：");
    QString recint=QString::number(recorde);
    painter.drawText(0,20,recstring+recint);

    //检查非free的子弹和敌机，使其图片移动（刚才是移动碰撞体积）
    //玩家飞机部分
    for(int i=0;i<BULLET_NUM;i++)
    {
         if(!my_plane->m_bullets[i].m_free)
         {
             painter.drawPixmap(my_plane->m_bullets[i].m_x,my_plane->m_bullets[i].m_y,my_plane->m_bullets[i].m_bullet);
         }
     }

    //小飞机子弹部分
     for(int i = 0 ; i< ENEMY_NUM;i++)
     {
         for(int j=0;j<3;j++)
         {
             if(m_enemys[i]->m_Free == false)
             {
                if(m_enemys[i]->mybullet[j].m_free==false)
                {
                    painter.drawPixmap(m_enemys[i]->mybullet[j].m_x,m_enemys[i]->mybullet[j].m_y,m_enemys[i]->mybullet[j].m_bullet);
                }

             }
         }
     }

     //中飞机子弹部分
     for(int i = 0 ; i< ENEMY_NUM2;i++)
     {
         for(int j=0;j<3;j++)
         {
             for(int k=0;k<5;k++)
             {
                 if(mid_enemys[i]->m_Free == false)
                 {
                    if(mid_enemys[i]->mybullet[j][k]->m_free==false)
                    {
                        painter.drawPixmap(mid_enemys[i]->mybullet[j][k]->m_x,mid_enemys[i]->mybullet[j][k]->m_y,mid_enemys[i]->mybullet[j][k]->m_bullet);
                    }

                 }
             }
         }
     }


     //小飞机部分
     for(int i = 0 ; i< ENEMY_NUM;i++)
     {
        if(m_enemys[i]->m_Free == false)
        {
             painter.drawPixmap(m_enemys[i]->m_x,m_enemys[i]->m_y,m_enemys[i]->m_enemy);
        }
     }

     //中飞机部分
     for(int i = 0 ; i< ENEMY_NUM2;i++)
     {
        if(mid_enemys[i]->m_Free == false)
        {
             painter.drawPixmap(mid_enemys[i]->m_x,mid_enemys[i]->m_y,mid_enemys[i]->Mid_enemy);
        }
     }

     //如果输了
     if(defeat())
     {

         //打印“游戏结束”以及分数
         painter.setFont(QFont("黑体",30));
         painter.drawText(0.5*GAME_WIDTH-90,0.5*GAME_HEIGHT-15,"游戏结束");
         painter.setFont(QFont("黑体",20));
         painter.drawText(0.5*GAME_WIDTH-60,0.5*GAME_HEIGHT+25,"得分："+QString::number(recorde));

     }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    //基本保证鼠标控制移动点在飞机图片的中央
    int x=event->x() - my_plane->m_Plane.width()*0.5;
    int y=event->y() - my_plane->m_Plane.height()*0.5;
    //如果鼠标超出屏幕，飞机不会飞出屏幕
    if(x<=0) x=0;
    if(x>=GAME_WIDTH-my_plane->m_Plane.width()) x=GAME_WIDTH+13-my_plane->m_Plane.width();
    if(y<=0) y=0;
    if(y>=GAME_HEIGHT-my_plane->m_Plane.height()) y=GAME_HEIGHT+13-my_plane->m_Plane.height();
    my_plane->setPosition(x,y);
}

void MainScene::enemyToScene()//小飞机
{
    m_recorder++;
    int a;

    if(recorde<=300) a=recorde/15;
    else if(recorde<=1000) a=21;
    else if(recorde<=1500) a=(recorde-900)/100+21;
    else a=28;

    if(m_recorder < ENEMY_INTERVAL-a)
    {
        return;
    }

    m_recorder = 0;
    //使敌机出现
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i]->m_Free)
        {
            m_enemys[i]->m_Free = false;
            //出现的位置随机，范围为[0~（窗口宽度-敌机碰撞体积）]
            m_enemys[i]->m_x = rand() % (GAME_WIDTH - m_enemys[i]->m_Rect.width());
            m_enemys[i]->m_y = -m_enemys[i]->m_Rect.height();
            break;
        }
    }
}

void MainScene::enemyToScene2()//中飞机
{
    m_recorder2++;
    int a;

    if(recorde<=650) a=recorde/25;
    else a=26;

    if(m_recorder2 < ENEMY_INTERVAL-a)
    {
        return;
    }

    m_recorder2 = 0;
    //使敌机出现
    for(int i=0;i<ENEMY_NUM2;i++)
    {
        if(mid_enemys[i]->m_Free)
        {
            mid_enemys[i]->m_Free = false;
            mid_enemys[i]->blood=BLOOD;
            //出现的位置随机，范围为[0~（窗口宽度-敌机碰撞体积）]
            mid_enemys[i]->m_x = rand() % (GAME_WIDTH - mid_enemys[i]->m_Rect.width());
            mid_enemys[i]->m_y = -mid_enemys[i]->m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()//检测飞机是否被玩家的子弹打中
{
    //遍历所有非空闲的敌机
    //小飞机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i]->m_Free)
        {
            continue;
        }
        //检查玩家的所有子弹
        for(int j=0;j<BULLET_NUM;j++)
        {
            if(my_plane->m_bullets[j].m_free)
            {
                continue;
            }
            //如果飞机被玩家的子弹打中
            if(m_enemys[i]->m_Rect.intersects(my_plane->m_bullets[j].m_Rect))
            {
                //飞机free
                m_enemys[i]->m_Free = true;
                //该飞机的子弹也free（已有的子弹就消失了）
                for(int j=0;j<3;j++)
                    m_enemys[i]->mybullet[j].m_free=true;
                //相当于初始化，m_recorder=80。
                m_enemys[i]->m_recorder=80;
                //玩家的这个子弹也free
                my_plane->m_bullets[j].m_free = true;
                //分数增加
                recorde++;
            }
        }
    }

    //中飞机
    for(int i=0;i<ENEMY_NUM2;i++)
    {
        if(mid_enemys[i]->m_Free)
        {
            continue;
        }
        //检查玩家的所有子弹
        for(int j =0; j<BULLET_NUM;j++)
        {
            if(my_plane->m_bullets[j].m_free)
            {
                continue;
            }
            //如果飞机被玩家的子弹打中
            if(mid_enemys[i]->m_Rect.intersects(my_plane->m_bullets[j].m_Rect))
            {
                mid_enemys[i]->blood--;

                //飞机free
                if(mid_enemys[i]->blood<=0)
                mid_enemys[i]->m_Free = true;

                //该飞机的子弹也free（已有的子弹就消失了）
                for(int j=0;j<3;j++)
                    for(int k=0;k<5;k++)
                        mid_enemys[i]->mybullet[j][k]->m_free=true;

                //该中飞机相当于初始化，m_recorder=80。
                mid_enemys[i]->m_recorder=80;
                //玩家的这个子弹也free
                my_plane->m_bullets[j].m_free = true;
                //分数增加
                recorde++;
            }
        }
    }
}


bool MainScene::defeat()//检测玩家是否被飞机打中
{
    //小飞机
    for(int i=0 ;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i]->m_Free)
        {
            continue;
        }
        //如果（非free）敌机与玩家飞机发生了碰撞，则游戏结束
        if(m_enemys[i]->m_Rect.intersects(my_plane->m_Rect))
        {
            QSound::play(":/res/biu_01.wav");

            //m->mediaStop2();
            return true;
        }
    }
    //中飞机
    for(int i=0;i<ENEMY_NUM2;i++)
    {
        if(mid_enemys[i]->m_Free)
        {
            continue;
        }
        //如果（非free）敌机与玩家飞机发生了碰撞，则游戏结束
        if(mid_enemys[i]->m_Rect.intersects(my_plane->m_Rect))
        {
            QSound::play(":/res/biu_01.wav");

            //m->mediaStop2();
            //m->mediaPlay1();
            return true;
        }
    }

        return false;
}

void MainScene::reshow()
{
    this->show();
}

void MainScene::keyPressEvent(QKeyEvent *ev)
{
    //如果按下了Esc键
    if(ev->key()==Qt::Key_Escape)
    {

       if(pausebtn->isHidden()) //若没在暂停则暂停，计时停止
       {
            pausebtn->show();
            pausebtn->move(pausebtn->myy,pausebtn->myx);
            m_Timer.stop();
       }
       else //若正在暂停，游戏继续，计时又开始
       {
            pausebtn->hide();
            m_Timer.start();
       }
    }

}

void MainScene::collisiondownrecorde()//检查玩家是否被子弹打中
{
    //小飞机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys[i]->m_Free)
        {
            continue;
        }

        for(int j = 0 ; j < 3;j++)
        {
            if(m_enemys[i]->mybullet[j].m_free)
            {
                continue;
            }
            //如果玩家被敌机子弹打中，分数减1
            if(m_enemys[i]->mybullet[j].m_Rect.intersects(my_plane->m_Rect))
            {
                m_enemys[i]->mybullet[j].m_free=true;
                if(recorde>=1)recorde--;
            }
        }
    }

    //中飞机
    for(int i=0;i<ENEMY_NUM2;i++)
    {
        if(mid_enemys[i]->m_Free)
        {
            continue;
        }

        for(int j = 0 ; j < 3;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(mid_enemys[i]->mybullet[j][k]->m_free)
                {
                    continue;
                }
                //如果玩家被敌机子弹打中，分数减1
                if(mid_enemys[i]->mybullet[j][k]->m_Rect.intersects(my_plane->m_Rect))
                {
                    mid_enemys[i]->mybullet[j][k]->m_free=true;
                    if(recorde>=1)recorde--;
                }
            }
        }
    }

}
