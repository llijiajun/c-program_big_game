//
//  Specs.hpp
//  CrazyArcade
//
//  Created by lizixian on 2018/5/22.
//  Copyright © 2018 lizixian. All rights reserved.
//

// 特殊道具对Player的影响逻辑未实现

#ifndef Specs_hpp
#define Specs_hpp

#include <iostream>
#include<QPainter>
using namespace std;

class Specs{
protected:
    int _locX;
    int _locY;
    string _effect;  // 效果
    double prob[2]; // 刷新几率
    static int size;
public:
    Specs(){
    }
    Specs(int x, int y, string eff);
    Specs(const Specs &S);
    void show(QPainter *painter, QImage specs);
    int getX()const;
    int getY()const;
    double getProbLow();
    double getProbHigh();
    string getEffect()const{return _effect;}
};

class Spec_Speed : public Specs{
public:
    Spec_Speed(int x, int y) : Specs(x, y, "Speed Up"){
        this->prob[0] = 0;
        this->prob[1] = 0.2;
    }
    Spec_Speed(const Spec_Speed &SS) : Specs(SS){}
};

class Spec_Power : public Specs{
public:
    Spec_Power(int x, int y) : Specs(x, y, "Power Up"){
        this->prob[0] = 0.2;
        this->prob[1] = 0.4;
    }
    Spec_Power(const Spec_Power &SS) : Specs(SS){}
};

class Spec_Limit : public Specs{
public:
    Spec_Limit(int x, int y) : Specs(x, y, "Limit Up"){
        this->prob[0] = 0.4;
        this->prob[1] = 0.6;
    }
    Spec_Limit(const Spec_Limit &SS) : Specs(SS){}
};

class Spec_Invul : public Specs{
public:
    Spec_Invul(int x, int y) : Specs(x, y, "Invul"){
        this->prob[0] = 0.6;
        this->prob[1] = 0.7;
    }
    Spec_Invul(const Spec_Invul &SS) : Specs(SS){}
};

class Spec_Spec1 : public Specs{
public:
    Spec_Spec1(int x, int y) : Specs(x, y, "Spec1"){
        this->prob[0] = 0.7;
        this->prob[1] = 0.8;
    }
    Spec_Spec1(const Spec_Spec1 &SS) : Specs(SS){}
};

class Spec_Spec2 : public Specs{
public:
    Spec_Spec2(int x, int y) : Specs(x, y, "Spec2"){
        this->prob[0] = 0.8;
        this->prob[1] = 0.9;
    }
    Spec_Spec2(const Spec_Spec2 &SS) : Specs(SS){}
};

class Spec_Points : public Specs{
public:
    Spec_Points(int x, int y) : Specs(x, y, "Points Up"){
        this->prob[0] = 0;
        this->prob[1] = 0.2;
    }
    Spec_Points(const Spec_Points &SS) : Specs(SS){}
};

#endif /* Specs_hpp */
