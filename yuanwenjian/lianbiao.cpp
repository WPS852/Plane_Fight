#include "lianbiao.h"
#include <QDebug>
#include <QDate>
Player::Player(){}
Player a[100];
//用于将文件数据读入动态链表中
Player* Player::createp()
{
    Player* pHead = new Player;
    pHead->next = NULL;
    FILE* fp = fopen("F:\\Rank.txt", "a+");
    fclose(fp);
    fp = fopen("F:\\Rank.txt", "rb");
    Player* cur = pHead;
    while (1)
    {
        Player* temp = new Player;
        if (!temp) exit(-1);
        if (!fread(temp, LEN, 1, fp))     //如果没读到
        {
            free(temp);
            break;
        }
            cur->next = temp;
            cur = temp;
            cur->next = NULL;
    }
    fclose(fp);
    return pHead;
}

//用于添加新的玩家
int Player::addplayers(int s)
{
    Player* head = createp();
    Player* temp = head->next;
    if (temp == NULL)
    {
        temp = new Player;
        head->next = temp;
    }
    else
    {
        while (temp->next)
        {
            temp = temp->next;
        }
        Player* last = new Player;
        temp->next = last;
        temp = last;
    }
    temp->next = NULL;
    temp->score=s;
    QDate date(QDate::currentDate());
    temp->y = date.year();
    temp->m = date.month();
    temp->d = date.day();

    FILE* fp = fopen("F:\\Rank.txt", "ab+");
    fwrite(temp, LEN, 1, fp);
    fclose(fp);
    return 1;
}

//用于对所有玩家信息进行读取并排序，取前六名登入排行榜
Player* Player::show()
{
    int max;                                //max是用来标记最大分数所在下标的
    int i,j,k;                            //i表示数组长度,jk是循环变量
    Player t;                               //交换用的中间变量

    for(i=0;i<100;i++)
        a[i].score=0;

    i=0;

    Player* head = createp();
    Player* temp=new Player;
    temp = head->next;

    while(temp!=NULL)
    {
        a[i].score=temp->score;
        a[i].y=temp->y;
        a[i].m=temp->m;
        a[i].d=temp->d;
        i++;
        temp=temp->next;
    }

    if(i>=100) qDebug()<<"No Way!";

    //选择排序
    if(i>=6)
    {
        for(j=0;j<6;j++)
        {
            max=j;
            for(k=j;k<i;k++)
            {
                if(a[k].score>a[max].score ||
                   a[k].score==a[max].score&&a[k].y>a[max].y ||
                   a[k].score==a[max].score&&a[k].y==a[max].y&&a[k].m>a[max].m ||
                   a[k].score==a[max].score&&a[k].y==a[max].y&&a[k].m==a[max].m&&a[k].d>a[max].d) max=k;
            }
            //实现交换
            t=a[j];
            a[j]=a[max];
            a[max]=t;
        }
    }
    else
    {
        for(j=0;j<i;j++)
        {
            max=j;
            for(k=j;k<i;k++)
            {
                if(a[k].score>a[max].score) max=k;
            }
            //实现交换
            t=a[j];
            a[j]=a[max];
            a[max]=t;
        }
    }
    return &a[0];
}
