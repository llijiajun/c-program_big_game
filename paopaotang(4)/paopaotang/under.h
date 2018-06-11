#ifndef UNDER_H
#define UNDER_H
#include<iostream>
#include<QPainter>
#include<QImage>
using namespace std;

class Under
{
public:
    Under();
    Under(int startX,int startY,int endX,int endY,string name){
        _endX = endX;
        _endY = endY;
        _name = name;
    }
    Under(const Under &u){
        _endX = u._endX;
        _endY = u._endY;
        _name = u._name;
    }
    Under operator =(const Under&u){
        _endX = u._endX;
        _endY = u._endY;
        _name = u._name;
    }

    void show(QPainter *painter,QImage under,QImage bound);
    int getendX()const{return _endX;}
    int getendY()const{return _endY;}
    int getstartX()const{return _startX;}
    int getstartY()const{return _startY;}
    string getname()const{return _name;}
private:
    int _startX,_startY,_endX,_endY;
    static int size;
    string _name;
};

#endif // UNDER_H
