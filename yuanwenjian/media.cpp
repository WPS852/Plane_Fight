#include "media.h"

media::media()
{

}

void media::mediaPlay1(){
    s1->play();
    s1->setLoops(-1);
}

void media::mediaStop1(){
    s1->stop();
}

void media::mediaPlay2(){
    s2->play();
    s2->setLoops(-1);
}

void media::mediaStop2(){
    s2->stop();
}

void media::mediaPlay3(){
    s3->play();
}

void media::mediaStop3(){
    s3->stop();
}

media *m = new media;
