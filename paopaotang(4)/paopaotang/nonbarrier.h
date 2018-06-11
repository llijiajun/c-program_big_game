#ifndef NONBARRIER_H
#define NONBARRIER_H
#include"box.h"
#include<QPainter>
#include<QImage>
#include<iostream>
using namespace std;

class Nonbarrier:public Box//可消灭的障碍物
{
public:
    Nonbarrier(){}
    Nonbarrier(int x,int y,string _name,string a):Box(x,y,_name),ID(a){}
    Nonbarrier operator =(const Nonbarrier&b){
        Box::operator =(b);
        this->ID = b.ID;
        return *this;
    }
    void show(QPainter *painter,QImage non);
    string getType()const{return "nonbarrier";}
    string getID()const{return ID;}
private:
    string ID;
};

#endif // NONBARRIER_H
