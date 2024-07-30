#include "startscene.h"
#include<QPainter>
#include<QPushButton>
#include<QDebug>
#include "QSound"
#include "media.h"
#include "restartscene.h"
//第一个界面，即含有开始按钮的界面
startscene::startscene(QWidget *parent) : QWidget(parent)
{
    extern media *m;
    m->mediaPlay1();
    //设置窗口大小
    this->setFixedSize(GAME_WIDTH+13,GAME_HEIGHT);
    //设置图标
    this->setWindowIcon(QIcon(GAME_ICON));

    //在窗口中定义一个开始游戏按钮（startbutton类）,构造函数中定义btntype=1
    button=new startbutton(1);
    button->setParent(this);

    //移动按钮
    button->move(button->myy+8,button->myx);

    connect(button,&startbutton::clicked,[=](){
      button->zoom1();     //设置按钮按下的动画
      button->zoom2();

        QTimer::singleShot(250,this,[=](){
            //按钮功能：隐藏主菜单，转移到帮助界面
            this->hide();
            myhelpscene=new helpscene();
            myhelpscene->show();
            myhelpscene->move(750,50);//将窗口移动到正常的位置
            connect(myhelpscene,&helpscene::sendend,[=](){
                //在帮助界面点击鼠标的功能：隐藏该窗口并弹出游戏窗口
                QTimer::singleShot(100,myhelpscene,[=](){
                    myhelpscene->hide();
                    mymainscene=new MainScene();
                    mymainscene->show();
                    mymainscene->move(750,50);//将窗口移动到正常的位置
                    reshow(); //重复刷新游戏背景，实现动画效果

                });

            });

        });

    });




    //在窗口中定义排行榜按钮（startbutton类）,构造函数中定义btntype=1
    button2=new startbutton(4);
    button2->setParent(this);

    //移动按钮
    button2->move(button->myy+8,button->myx+100);

    connect(button2,&startbutton::clicked,[=](){
      button2->zoom3();     //设置按钮按下的动画
      button2->zoom4();

        QTimer::singleShot(250,this,[=](){
            //按钮功能： 打开帮助界面
            //this->hide();
            mypaihangbang=new paihangbang();
            mypaihangbang->show();
            mypaihangbang->move(750,300);//将窗口移动到正常的位置
            connect(mypaihangbang,&paihangbang::sendend,[=](){
                //可以模仿以下注释的这段代码补充功能，也可以全部删掉不用   ——小白
                //QTimer::singleShot(100,myhelpscene,[=](){
                    //myhelpscene->hide();
                    //mymainscene=new MainScene();
                    //mymainscene->show();
                    //mymainscene->move(750,100);//将窗口移动到正常的位置
                    //reshow(); //重复刷新游戏背景，实现动画效果

                //});

            });

        });

    });
}

void startscene::paintEvent(/*QPaintEvent *ev*/)
{
    //画出初始背景，与游戏刚开始时的相同
    QPainter painter(this);
    painter.drawPixmap(0,mymap.m_map1_posY,mymap.m_map1);
    painter.drawPixmap(0,mymap.m_map2_posY,mymap.m_map2);

    //显示标题图片(需要显示在上层所以要后画)
    title.load(TITLE_PATH);   //加载图片
    painter.drawPixmap(GAME_WIDTH*0.5-title.width()*0.5,title.height()+20,title);
}

void startscene::reshow()
{
    //接收重新开始信号
    connect(mymainscene,&MainScene::sendreshow,[=](){
        //创建新的对象，重新开始
        delete mymainscene;
        mymainscene=new MainScene();
        mymainscene->show();
        mymainscene->move(750,50);
        reshow();
    });

}
