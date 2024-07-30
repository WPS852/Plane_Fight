#ifndef STARTSCENE_H
#define STARTSCENE_H
#include <QWidget>
#include"config.h"
#include<QTimer>
#include"mainscene.h"
#include"startbutton.h"
#include"map.h"
#include"helpscene.h"
#include<QPixmap>
#include "paihangbang.h"

class startscene : public QWidget
{
    Q_OBJECT
public:
    explicit startscene(QWidget *parent = nullptr);
    void paintEvent(/*QPaintEvent *ev*/);    //画背景和标题图片
    void reshow();

    startbutton *button,*button2;
    MainScene *mymainscene;
    Map mymap;
    helpscene *myhelpscene;
    paihangbang *mypaihangbang;
    QPixmap title;
signals:

};

#endif // STARTSCENE_H
