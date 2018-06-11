#include "pitfall.h"
#include"box.h"
#include<QPainter>
#include<QImage>
#include<iostream>
using namespace std;
void Pitfall::show(QPainter *painter, QImage pit){
    if(name == "trans1")
    {
        name = "trans";
        ID = 1;
    }
    if(name == "trans2")
    {
        name = "trans";
        ID = 2;
    }
    painter->drawImage(PosX*size,PosY*size+40,pit);
}
