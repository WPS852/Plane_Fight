#ifndef LIANBIAO_H
#define LIANBIAO_H
#define LEN sizeof(Player)
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextBrowser>
#include <QTextStream>
#include <iostream>
#include <QFileInfo>
#include <QWidget>

class Player    //链表
{
public:
    int score;              //得分
    int y,m,d;              //时间
    Player* next;

    Player();
    static Player* createp();
    static int addplayers(int s);
    static Player* show();
};

#endif // LIANBIAO_H
