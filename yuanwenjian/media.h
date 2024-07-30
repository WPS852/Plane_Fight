#ifndef MEDIA_H
#define MEDIA_H
#include "QSound"

class media
{
public:
    media();
    void mediaPlay1();
    void mediaStop1();
    void mediaPlay2();
    void mediaStop2();
    void mediaPlay3();
    void mediaStop3();
private:
    QSound *s1=new QSound(":/res/memu_01.wav");
    QSound *s2=new QSound(":/res/1_01.wav");
    QSound *s3=new QSound(":/res/ziu_01.wav");
};

#endif // MEDIA_H
