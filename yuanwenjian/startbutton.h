#ifndef STARTBUTTON_H
#define STARTBUTTON_H
#include<QPixmap>
#include"config.h"
#include<QPushButton>
#include<QSize>
class startbutton:public QPushButton
{

public:
    startbutton(int btntype); //按钮类型
    void zoom1();             //动画
    void zoom2();
    void zoom3();
    void zoom4();
public:
    int myx;
    int myy;
    QPixmap mystartbutton,mystartbutton2;    //按钮图片
    QRect startbuttonrect;    //按钮的大小
};

#endif // STARTBUTTON_H
