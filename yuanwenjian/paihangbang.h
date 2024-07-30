#ifndef PAIHANGBANG_H
#define PAIHANGBANG_H
#include <QMainWindow>
#include<QPixmap>
#include"map.h"
#include <QWidget>
#include <QPainter>

class paihangbang : public QMainWindow
{
    Q_OBJECT
public:
    explicit paihangbang(QWidget *parent = nullptr);
    Map mymap;
    QPixmap tab[6];

    void paintEvent(QPaintEvent *ev);

signals:
    void sendend();
public slots:
};

#endif // PAIHANGBANG_H
