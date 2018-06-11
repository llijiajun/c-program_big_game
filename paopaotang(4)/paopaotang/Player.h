//
//  Player.hpp
//  CrazyArcade
//
//  Created by lizixian on 2018/5/21.
//  Copyright 漏 2018 lizixian. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Bomb.h"
#include "score.h"
#include<QPainter>
using namespace std;

class Player{
private:
    int _ID; // 鏍囪瘑鐜╁
    int _speed = 1; // 绉诲姩閫熷害
    int _lives = 2; // 鍓╀綑鍛芥暟
    int _power = 1; // 璇ョ帺瀹舵斁缃殑鐐稿脊鐨勭垎鐐稿▉鍔?鍗佸瓧鍨?
    int _bombLim = 1; // 鑳芥斁缃殑鐐稿脊涓婇檺
    bool _invul = false; // 鏄惁鏃犳晫
    bool _key = true; // 1-wasd+space; 0-鈫戔啌鈫愨啋+enter
    int _locX;
    int _locY;
    int _points; // 褰撳墠寰楀垎
    bool _spec1 = false; // 鏈夋病鏈夋墜鏋?
    bool _spec2 = false; // 鏈夋病鏈夐敜瀛?
    //鏇存敼鍐呭
    int direction;//浜虹墿鏂瑰悜锛?涓嬶紝2涓婏紝3宸︼紝4鍙?
    static int Size;//浜虹墿澶у皬
    static int moveSpeed;//涓€涓瓑绾ф墍浠ｈ〃鐨勭粷瀵圭Щ鍔ㄩ€熷害
    static int dir;
    bool _gun;//鍒ゆ柇浜虹墿鏄惁鏈夋縺鍏夋灙
    Score scores; //缁熻寰楀垎
public:
    Player(){direction = 1;_gun = false;}//浜虹墿寮€濮嬫椂鏂瑰悜鏈濅笅
    Player(int id, int x, int y);
    Player(const Player &p);
    void setDirection(int x){direction = x;}//璁剧疆鏂瑰悜锛屼娇寰楁墦寮€鐨勫浘鐗囦笌鎿嶄綔鏂瑰悜涓€鑷?
    int getDirection()const{return direction;}
    void show(QPainter *painter);//缁樺埗浜虹墿
    void setGun(bool gun);//浣╂埓婵€鍏夋灙
    string getAttackType();
    void setX(int x){_locX = x;}
    void setY(int y){_locY = y;}
    bool move(int dir);
    int getID();
    void speedUp();
    int getSpeed();
    bool die();
    int getLives();
    int getPower();
    void powerUp();
    int getBlim();
    void blimUp();
    bool getInv();
    void setInv(bool v);
    bool getSpec1();
    void setSpec1(bool v);
    bool getSpec2();
    void setSpec2(bool v);
    bool getKey();
    void setKey(bool v);
    int getPoints();
    void incPoints(int incre);
    void lifeup();
    void addScore();
    int getX()const;//鏇存敼
    int getY()const;//鏇存敼
    int getScore();
    int setScore(int s){scores.set(s);}
};
#endif /* Player_hpp */
