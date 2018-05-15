#ifndef PLAYER_H
#define PLAYER_H
#include "rpgobj.h"

class Player: public RPGObj
{
public:
    Player(){}
    ~Player(){}
    void move(int direction, int steps=1);
        //direction =1,2,3,4 for 上下左右
};

#endif // PLAYER_H
