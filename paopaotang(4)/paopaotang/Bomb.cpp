//
//  Bomb.cpp
//  CrazyArcade
//
//  Created by lizixian on 2018/5/21.
//  Copyright 漏 2018 lizixian. All rights reserved.
//

#include "Bomb.h"
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include<QPainter>
#include<QImage>
#include<QtMultimedia/QMediaPlayer>

using namespace std;
int Bomb::_timeTo = 3;
int Bomb::size = 80;

void Bomb::show(QPainter *painter, QImage bomb){
    /*QImage bomb;
    bomb.load("E:/image/bomb.png");*/
    painter->drawImage(_locX*size,_locY*size+40,bomb);
}
