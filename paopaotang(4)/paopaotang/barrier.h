#ifndef BARRIER_H
#define BARRIER_H
#include"box.h"
#include<QImage>
#include<QPainter>
using namespace std;

class Barrier:public Box//不可消灭的障碍物
{
public:
    Barrier();
    Barrier(int x,int y,string _name):Box(x,y,_name){}
    Barrier(const Barrier & b):Box(b){}
    Barrier operator =(const Barrier&b){
        Box::operator =(b);
        return *this;
    }

    void show(QPainter *painter,QImage bar);
    string getType()const{return "barrier";}
private:

};

#endif // BARRIER_H
