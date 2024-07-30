#include "mainscene.h"
#include<QResource>
#include <QApplication>
#include"config.h"
#include"startscene.h"
#include"restartscene.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startscene w;
    w.show();
    w.move(750,50);    //移动初始页面
    return a.exec();
}
