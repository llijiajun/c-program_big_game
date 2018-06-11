#ifndef Bomb_hpp
#define Bomb_hpp
#include "time.h"
#include<QPainter>
#include<QImage>
#include <iostream>
#include <objbase.h>
#include <stdio.h>
#define GUID_LEN 64
using namespace std;

class Bomb{
private:
    int _belongTo; // 灞炰簬鏌愪釜PlayerID
    int _power;
    int _locX;
    int _locY;
    int _BID;
    time_t _setTime;
    static int size;
public:
    static int _timeTo; // n绉掑悗鐖嗙偢
    Bomb(){
        this->_power = 1;
        this->_belongTo = 1;
    }
    Bomb(int x, int y, int p, int bT, int bid){
        this->_locX = x;
        this->_locY = y;
        this->_power = p;
        this->_belongTo = bT;
        time(&this->_setTime);
        this->_BID = bid;
    }
    Bomb(const Bomb &B){
        this->_locX = B._locX;
        this->_locY = B._locY;
        this->_power = B._power;
        this->_setTime = B._setTime;
        this->_belongTo = B._belongTo;
        this->_BID = B._BID;
        // cout << "In copy constructor" << endl;
    }
    ~Bomb(){}
    int getX()const{return _locX;}//鏇存敼
    int getY()const{return _locY;}//鏇存敼
    int getPower()const{return _power;}
    int getBelongTo() const{return _belongTo;}
    int getTimeTo() const {return _timeTo;}
    int getBID() {return _BID;}
    void show(QPainter *painter,QImage bomb);//缁樺埗鐐稿脊

    //void cThread(); // 鍒涘缓绾跨▼澶勭悊寤惰繜鐖嗙偢
};
#endif /* Bomb_hpp */
