#ifndef BOX_H
#define BOX_H
#include<QPainter>
using namespace std;

class Box//方块类
{
public:
    Box();
    Box(int x,int y,string a){
        PosX = x;
        PosY = y;
        name = a;
    }
    virtual ~Box(){}
    Box(const Box &b){PosX=b.PosX;PosY=b.PosY;name = b.name;}
    Box& operator =(const Box&b){PosX=b.PosX;PosY=b.PosY;name = b.name;}
    //virtual void show(QPainter *painter);
    virtual string getType()const{return "box";}
    int getX()const{return PosX;}
    int getY()const{return PosY;}
protected:
    int PosX,PosY;
    static int size;
    string name;
};

#endif // BOX_H
