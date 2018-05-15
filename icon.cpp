#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;


pair<string,ICON> pairArray[] =
{
    make_pair("player",ICON("player",1,13, 1, 2)),
    make_pair("stone",ICON("stone",4,9, 1, 1)),
    make_pair("fruit",ICON("fruit",3,6, 1, 1)),
    make_pair("monster",ICON("monster",3,1,1,1)),
    make_pair("left_top",ICON("left_top",11,13,1,1)),
    make_pair("right_top",ICON("right_top",13,13,1,1)),
    make_pair("building_top",ICON("building_top",12,4,4,3)),
    make_pair("building_bot",ICON("buiding_bot",8,7,4,3)),
    make_pair("building_bot2",ICON("building_bot2",8,4,4,3)),
    make_pair("top_hen",ICON("top_hen",12,13,1,1)),
    make_pair("right_hen",ICON("right_hen",13,14,1,1)),
    make_pair("right_bot",ICON("right_bot",13,15,1,1)),
    make_pair("bot_hen",ICON("bot_hen",12,15,1,1)),
    make_pair("left_bot",ICON("left_bot",11,15,1,1)),
    make_pair("left_hen",ICON("left_hen",11,14,1,1)),
    make_pair("tomato",ICON("tomato",12,3,4,1)),
    make_pair("brown_road31",ICON("brown_road31",3,2,3,1)),
    make_pair("clothes",ICON("clothes",13,11,3,1)),
    make_pair("well",ICON("well",13,12,1,1))
};

map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
}

ICON ICON::findICON(string type){
    map<string,ICON>::iterator kv;
    kv = ICON::GAME_ICON_SET.find(type);
    if (kv==ICON::GAME_ICON_SET.end()){

       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}
