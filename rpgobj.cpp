#include "rpgobj.h"
#include <iostream>

using namespace std;

void RPGObj::initObj(string type)
{
    //TODO 所支持的对象类型应定义为枚举
    if (type.compare("player")==0){
        this->_coverable = false;
        this->_eatable = false;
        this->_hurt=false;
    }
    else if (type.compare("stone")==0){
        this->_coverable = false;
        this->_eatable = false;
        this->_hurt=false;
    }
    else if (type.compare("fruit")==0){
        this->_coverable = false;
        this->_eatable = true;
        this->_hurt=false;
    }
    else if (type.compare("monster")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=true;
    }
    else if (type.compare("left_top")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("right_top")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("building_top")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("building_bot")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("building_bot2")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("tomato")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("top_hen")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("right_hen")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("right_bot")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("bot_hen")==0){
        this->_coverable=false;
        this->_eatable=false;
    }
    else if (type.compare("left_bot")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("left_hen")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("brown_road31")==0){
        this->_coverable=true;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("clothes")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else if (type.compare("well")==0){
        this->_coverable=false;
        this->_eatable=false;
        this->_hurt=false;
    }
    else{
        //TODO 应由专门的错误日志文件记录
        cout<<"invalid ICON type."<<endl;
        return;
    }

    this->_icon = ICON::findICON(type);
    QImage all;
    all.load("C://work/practice/QTMap/TileB.png");
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));

}

void RPGObj::show(QPainter * pa){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,(this->_pos_y)*gSize,this->_pic);
    //cout<<"888"<<this->_pos_x<<","<<this->_pos_y<<endl;
}



