//
//  Player.cpp
//  CrazyArcade
//
//  Created by lizixian on 2018/5/21.
//  Copyright 漏 2018 lizixian. All rights reserved.
//

#include "Player.h"
#include"Bomb.h"
#include<QImage>
#include<QPainter>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<sstream>
using namespace std;
int Player::dir = 1;
int Player::Size = 80;//浜虹墿澶у皬
int Player::moveSpeed = 10;//涓€涓瓑绾ф墍浠ｈ〃鐨勭粷瀵圭Щ鍔ㄩ€熷害
Player::Player(int id, int x, int y){
    this->_locX = x;
    this->_locY = y;
    this->_ID = id;
    direction = 1;
    _gun = false;
}

Player::Player(const Player &p){
    this->_spec1 = p._spec1;
    this->_spec2 = p._spec2;
    this->_locX = p._locX;
    this->_locY = p._locY;
    this->_points = p._points;
    this->_speed = p._speed;
    this->_lives = p._lives;
    this->_power = p._power;
    this->_bombLim = p._bombLim;
    this->_invul = p._invul;
    this->_key = p._key;
    this->_ID = p._ID;
    this->_gun = p._gun;
}
void Player::setGun(bool gun){
    if(gun)
        _gun = true;
    else
        _gun = false;
}

void Player::show(QPainter *painter){
    QImage _player;
    string file = "E:/image/character/";
    ostringstream os1,os2,os3;
    os1<< _ID;
    file += os1.str();
    file += ".";
    os2<< direction;
    file += os2.str();
    if(_gun)
        file += "gun";
    /*os3<<dir;
    file += os3.str();
    file += ".png";*/
    _player.load(file.c_str());
    painter->drawImage(_locX,_locY+40,_player);
    dir++;
    /*if(dir>4)
        dir-=4;*/
}//缁樺埗浜虹墿
string Player::getAttackType(){
    if(_gun)
        return "gun";
    return "bomb";
}

int Player::getID(){
    return this->_ID;
}

void Player::speedUp(){
    if (this->_speed < 3) this->_speed += 1;
    return;
}

int Player::getSpeed(){
    return this->_speed;
}

bool Player::die(){
    this->_lives -= 1;

    scores.mins(50);

    if (this->_lives == 0){
        return true;
    }
    return false;
}

int Player::getLives(){
    return this->_lives;
}

void Player::powerUp(){

    scores.add(10);

    if (this->_power < 5) this->_power += 1;
    return;
}

int Player::getPower(){
    return this->_power;
}

int Player::getBlim(){
    return this->_bombLim;
}

void Player::blimUp(){

    scores.add(10);

    if (this->_bombLim < 5) this->_bombLim += 1;
    return;
}
void Player::lifeup(){

    scores.add(10);

    if(this->_lives < 5)
        this->_lives++;
    return;
}

bool Player::getInv(){
    return this->_invul;
}

void Player::setInv(bool v){
    this->_invul = v;
}

bool Player::getKey(){
    return this->_key;
}

void Player::setKey(bool v){
    this->_key = v;
}

int Player::getPoints(){
    return this->_points;
}

void Player::incPoints(int incre){
    if (incre <= 0) return; // 杩橀渶瑕佸incre杩涜妫€鏌??
    else this->_points += incre;
}

int Player::getX()const{
    return this->_locX;
}

int Player::getY() const{
    return this->_locY;
}

bool Player::move(int dir){
    direction = dir;
    switch(dir){
        // 妫€鏌ユ槸鍚﹀嚭鍦板浘杈圭晫 ?
        case 1:
            this->_locY += _speed*moveSpeed;//绉诲姩閫熷害绛変簬褰撳墠閫熷害绛夌骇涔樹竴绾ф墍浠ｈ〃鐨勭粷瀵归€熷害
            return true;
        case 2:
            this->_locY -= _speed*moveSpeed;
            return true;
        case 3:
            this->_locX -= _speed*moveSpeed;
            return true;
        case 4:
            this->_locX += _speed*moveSpeed;
            return true;
    }
    return true;
}

bool Player::getSpec1(){
    return this->_spec1;
}

void Player::setSpec1(bool v){
    this->_spec1 = v;
}

bool Player::getSpec2(){
    return this->_spec2;
}

void Player::setSpec2(bool v){
    this->_spec2 = v;
}
void Player::addScore(){
    scores.add(10);
}

int Player::getScore(){
    return scores.getScore();
}
