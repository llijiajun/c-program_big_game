#ifndef PITFALL_H
#define PITFALL_H
#include<iostream>
#include<QPainter>
#include<QImage>
#include"box.h"
using namespace std;

class Pitfall:public Box//陷阱类
{
public:
    Pitfall(){}
    Pitfall(int x,int y,string a):Box(x,y,a){}
    void show(QPainter *painter,QImage pit);
    Pitfall operator =(const Pitfall&b){
        Box::operator =(b);
        return *this;
    }
    string getType()const{return "pitfall";}
    string getname()const{return name;}
    int getID()const{return ID;}
private:
    int ID;
};

#endif // PITFALL_H
