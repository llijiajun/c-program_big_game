//
//  Specs.cpp
//  CrazyArcade
//
//  Created by lizixian on 2018/5/22.
//  Copyright © 2018 lizixian. All rights reserved.
//

#include "Specs.h"
#include<QPainter>
#include<QImage>
int Specs::size = 80;
Specs::Specs(int x, int y, string eff){
    this->_locX = x;
    this->_locY = y;
    this->_effect = eff;
}

Specs::Specs(const Specs &S){
    this->_locX = S._locX;
    this->_locY = S._locY;
    this->_effect = S._effect;
    this->prob[0] = S.prob[0];
    this->prob[1] = S.prob[1];
}

int Specs::getX() const{
    return this->_locX;
}

int Specs::getY()const{
    return this->_locY;
}

double Specs::getProbLow(){
    return this->prob[0];
}

double Specs::getProbHigh(){
    return this->prob[1];
}
void Specs::show(QPainter *painter, QImage specs){
    painter->drawImage(_locX*size,_locY*size+40,specs);
}

