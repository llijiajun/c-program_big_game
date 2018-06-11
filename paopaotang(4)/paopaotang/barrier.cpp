#include"box.h"
#include "barrier.h"
#include<QImage>
#include<QPainter>
#include<iostream>
using namespace std;
Barrier::Barrier(){

}

void Barrier::show(QPainter *painter,QImage bar){
    /*QImage bar;
    string file;
    file = "E:/image/";
    file += name;
    file += "/1.png";
    bar.load(file.c_str());*/
    painter->drawImage(PosX*size,PosY*size+20,bar);

}
