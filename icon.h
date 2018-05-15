#ifndef ICON_H
#define ICON_H
#include <string>
#include <map>
using namespace std;

//将一类图标定位到素材图片上的具体区域
class ICON
{
public:
    static int GRID_SIZE;//游戏中一格，相当于图片中多少像素
    static map<string,ICON> GAME_ICON_SET;
        //确定各类物体子素材图片的位置，高、宽等数据
    static ICON findICON(string type);
        //根据物体类型名找到图标

    ICON(){}
    ICON(string name, int x, int y, int w, int h);
    string getTypeName() const{return this->typeName;}
    int getSrcX() const{return this->srcX;}
    int getSrcY() const{return this->srcY;}
    int getWidth() const{return this->width;}
    int getHeight() const{return this->height;}

private:
    string typeName;
    int srcX, srcY, width, height;

};

#endif // ICON_H
