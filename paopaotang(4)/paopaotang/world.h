#ifndef WORLD_H
#define WORLD_H
#include<QPainter>
#include<vector>
#include<QImage>
#include"Player.h"
#include"Bomb.h"
#include"Specs.h"
#include"box.h"
#include"barrier.h"
#include"nonbarrier.h"
#include"under.h"
#include"pitfall.h"
#include<QtMultimedia/QMediaPlayer>
class World
{
public:
    World();
    void read(){_save = true;}//设置为读档
    void initWorld();//设置属性
    void initImage(string mapname);
    void show(QPainter *painter);//绘制游戏界面
    void handlemove(int ID, int direction);//人物移动
    void attack(int ID);//放置炸弹
    void AttackGif(QPainter *painter, int ID);//绘制动画
    static void* explore(void *args);//销毁炸弹和炸毁的物体
    static void* giftime(void *att);//设置激光攻击动画
    void erasemap();
    int **AttackDetect(string type, int x, int y, int ID);//返回被销毁的图像位置坐标数组,参数为攻击方式、攻击点坐标
    template<class T>
    bool movedetect(int direction,const Player &player,vector<T> box);//检测人物是否能通行
    void eatspecs(Player &player);//拾取道具
    void pitdetect(Player &player);
    int getendX()const{return _under.getendX();}
    int getendY()const{return _under.getendY();}
    int getplayerX(int ID)const{return _player[ID-1].getX();}
    int getplayerY(int ID)const{return _player[ID-1].getY();}
    int map[20][20];//用于判断当前坐标下是否有物体
    void harm(int ID, string type);//用于判定人物是否收到伤害,ID用于激光攻击时计算伤害
    void playerdie(int ID);//人物生命值减少
    static void PlayMusic(string type);
    void save();
    Player _player[2];
    //void erasebomb();
private:
    //vector<Player> _player;

    vector<Bomb> _bomb;
    vector<Specs> _specs;
    vector<Box> _box;
    vector<Barrier> _bar;
    vector<Nonbarrier> _non;
    vector<Pitfall> _pitfall;
    Under _under;
    QImage i_barrier,i_nonbarrier[2],i_pitfall[3],i_bomb,i_specs[8],i_under,i_bound;
    QImage center[5], wave[2][4];
    string mapname;
    bool _save;//判断是否是读档
};
template<class T>
bool World::movedetect(int direction,const Player &player,vector<T> box){
    if(player.getX()==(_under.getstartX()+1)*80&&direction == 3)
        return false;
    if(player.getX()+80==_under.getendX()*80+80&&direction == 4)
        return false;
    if(player.getY()==(_under.getstartY()+1)*80&& direction == 2)
        return false;
    if(player.getY()+80==_under.getendY()*80+80&& direction == 1)
        return false;
    for(int i = 0 ;i < box.size();i++)
    {
        if(direction == 1 ||direction == 2)//上下移动比较Y坐标
        {
            if(!(box[i].getX()*80>= player.getX()+50||box[i].getX()*80+80<= player.getX()+30) )// 可能无法通过的条件是人物和炸弹的X有相交部分
            {
                if(direction == 1&&box[i].getY()*80 == player.getY()+80)
                    return false;
                if(direction == 2&&box[i].getY()*80+80== player.getY()+60)
                    return false;
            }
        }
        else//左右移动比较X坐标
        {
            if(!(box[i].getY()*80>= player.getY()+80||box[i].getY()*80+80<= player.getY()+60))// 可能无法通过的条件是人物和炸弹的Y相等
            {
                if(direction == 3&&box[i].getX()*80+80 == player.getX()+20)
                    return false;
                if(direction == 4&&(box[i].getX() )*80== player.getX()+60)
                    return false;
            }
        }
    }
    return true;
}//判断人物是否能够移动

#endif // WORLD_H
