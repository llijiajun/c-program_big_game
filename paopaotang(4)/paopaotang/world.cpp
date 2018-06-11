#include "world.h"
#include"Player.h"
#include"Bomb.h"
#include"Specs.h"
#include"box.h"
#include"barrier.h"
#include"pitfall.h"
#include<QPainter>
#include<QImage>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<fstream>
#include <unistd.h>
#include <pthread.h>
#include<QtMultimedia/QMediaPlayer>
#include<sstream>
#include<QMessageBox>
using namespace std;
int BombCount = 0;
bool laserAttack[2] = {0};//人物激光攻击动画是否绘制
int bombAttack[20][20] = {0};
bool erase[20][20] = {0};
bool blast[20][20] = {0};//判断当前位置炸弹是否爆炸
struct Args{
    int ID;
    int timeTo;
    int power;
    int x;
    int y;
    int BID;
    vector<Bomb>* pBombs;
    vector<Nonbarrier>* pNons;
    vector<Specs>* pSpecs;
    int **destroy;
};
struct Blast{
    int x;
    int y;
    QPainter *painter;
};
struct laser{
    int ID;
    Player *player;
    int **destroy;
    vector<Nonbarrier>* pNons;
    vector<Specs>* pSpecs;
};

World::World(){
    for(int i = 0;i < 20;i++)
    {
        for(int j = 0;j < 20;j++)
            map[i][j] = 0;
    }
    this->_save = false;
}
void World::initWorld(){
    ifstream fin;
    if(_save)
        fin.open("E:/image/map-save.txt");
    else
        fin.open("E:/image/map.txt");
    string classname,subclassname,ch,ID;
    int endX,endY,x,y;
    fin >> mapname >> endX >> endY;
    Player _play(1,80,80);
    _player[0] = _play;
    Player _play1(2,1200,800);
    _player[1] = _play1;
    Under under(0,0,endX,endY,mapname);
    _under = under;
    this->initImage(mapname);
    for(int i = 0; ;i++)
    {
        if(fin.eof())
        {
            break;
        }
        fin >> classname;
        if(classname == "playerscore")
        {
            fin >> x;
            fin >> y;
            _player[x-1].setScore(y);
            continue;
        }
        if(classname == "specs"||classname == "pitfall")
            fin >> subclassname;
        fin >> x >> y;
        if(classname == "barrier")
        {
            Barrier bar(x,y,mapname);
            _bar.push_back(bar);
        }
        else if(classname == "nonbarrier")
        {
            fin >> ID;
            Nonbarrier non(x,y,mapname,ID);
            _non.push_back(non);
        }
        else if(classname == "specs")
        {
            Specs specs(x,y,subclassname);
            _specs.push_back(specs);
        }
        else if(classname == "pitfall")
        {
            Pitfall pit(x,y,subclassname);
            _pitfall.push_back(pit);
        }
        if(classname != "pitfall")
            map[y][x] = 1;
    }
    for(int i = 1;i <= endY;i++)
    {
        for(int j = 1;j <= endX;j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}//创建游戏
void World::initImage(string mapname){
    string file = "E:/image/";
    {
        string ch = file;
        ch += mapname;
        ch += "/1.png";
        i_barrier.load(ch.c_str());
    }
    {
        string ch = file;
        ch += "/bomb.png";
        i_bomb.load(ch.c_str());
    }
    {
        string ch1 = file + mapname;
        string ch2 = ch1;
        ch1 += "/2.png";
        ch2 += "/3.png";
        i_nonbarrier[0].load(ch1.c_str());
        i_nonbarrier[1].load(ch2.c_str());
    }
    {
        string ch1 = file + mapname;
        string ch2 = ch1;
        ch1 += "/under0.png";
        ch2 += "/bound.png";
        i_under.load(ch1.c_str());
        i_bound.load(ch2.c_str());
    }
    {
        string ch1 = file;
        ch1 += "pitfall/";
        string ch2,ch3;
        ch2 = ch1;
        ch3 = ch1;
        ch1 += "left.png";
        ch2 += "right.png";
        ch3 += "trans.png";
        i_pitfall[0].load(ch1.c_str());
        i_pitfall[1].load(ch2.c_str());
        i_pitfall[2].load(ch3.c_str());
    }
    {
        string ch[8];
        for(int i = 0;i < 8;i++)
        {
            ch[i] = file;
            ch[i] += "specs/";
        }
        ch[0] += "addhp.png";
        ch[1] += "gun.png";
        ch[2] += "hammer.png";
        ch[3] += "invul.png";
        ch[4] +="powerup.png";
        ch[5] += "pushbomb.png";
        ch[6] += "speedup.png";
        ch[7] += "limitup.png";
        for(int i = 0;i < 7;i++)
        {
            i_specs[i].load(ch[i].c_str());
        }
    }
    {
        center[0].load("E:/image/bomb/center1.png");
        center[1].load("E:/image/bomb/center2.png");
        center[2].load("E:/image/bomb/center3.png");
        center[3].load("E:/image/bomb/center4.png");
        center[4].load("E:/image/bomb/center5.png");
        wave[0][3].load("E:/image/bomb/wavelateral.png");
        wave[1][3].load("E:/image/bomb/wavevertical.png");
        for(int i = 0;i < 3;i++)
            wave[0][i] = wave[0][3].copy(0,0,i*80+30,80);//加载横向不同长度爆炸波图片
        for(int i = 0;i < 3;i++)
            wave[1][i] = wave[1][3].copy(0,0,80,i*80+30);//加载纵向不同长度爆炸波图片
    }
}//存入图像信息


void* World::explore(void *args){
    struct Args *pst;
    pst = (struct Args *) args;
    int timeTo = pst->timeTo;
    int ID = pst->ID;
    int power = pst->power;
    int X = pst->x;
    int Y = pst->y;
    int bid = pst->BID;
    vector<Bomb>* pbs = pst->pBombs;
    vector<Nonbarrier>* non = pst->pNons;
    vector<Specs>* specs = pst->pSpecs;
    sleep(timeTo);
    printf("Bomb%d by player%d exploded\n",bid ,ID);

    vector<Bomb>::iterator it;
    cout << "Power: " << power << endl;
    cout << 222 << endl;
    for(it=pbs->begin();it!=pbs->end(); ){
        if (it->getBID() == bid){
            pbs->erase(it);
            if(pbs->end()==it)
                break;
            continue;
        }
        it++;
    }
    /*for(it=pbs->begin();it!=pbs->end();it++)
    {
        if (it->getBID() == bid)
        {
            pbs->erase(it);
             it--;
        }
        if(pbs->end()==it)
            break;
    }*/
    World::PlayMusic("bomb");
    for(int i = 1;i <= 5;i++)
    {
        Sleep(80);
        bombAttack[Y][X] = i;
    }
    blast[Y][X] = true;
    Sleep(200);
    bombAttack[Y][X] = 0;
    vector<Nonbarrier>::iterator it1;
    for(it1 = non->begin();it1!=non->end();it1++)
    {
        for(int i = 0;i < 4;i++)
        {
            if(it1->getX() == pst->destroy[i][0] && it1->getY() == pst->destroy[i][1])
            {
                non->erase(it1);
                erase[pst->destroy[i][1]][pst->destroy[i][0]] = true;
                break;
            }
        }//对比坐标
        if(non->end() == it1)
            break;
    }

    vector<Specs>::iterator it2;
    for(it2 = specs->begin();it2!=specs->end();it2++)
    {
        for(int i = 0;i < 4;i++)
        {
            if(it2->getX() == pst->destroy[i][0] && it2->getY() == pst->destroy[i][1])
            {
                specs->erase(it2);
                erase[pst->destroy[i][1]][pst->destroy[i][0]] = true;
                break;
            }
        }
        if(specs->end() == it2)
            break;
    }

    delete(pbs);
    return NULL;
}//销毁炸弹和爆炸波及的物体，设置爆炸波时间
void World::attack(int ID){
    if(_player[ID-1].getAttackType() == "bomb")
    {

        int x = (_player[ID-1].getX()+40)/80;
        int y = (_player[ID-1].getY()+80)/80;
        if(map[y][x] == 1)
            return;
        Bomb bomb(x,y,1,1, BombCount);
        _bomb.push_back(bomb);
        cout << "BombCount: " << BombCount << endl;
        printf("Bomb%d set by player%d\n", bomb.getBID(), ID);
        pthread_t pid;
        Args *args = new Args();
        args->ID = ID;
        args->timeTo = Bomb::_timeTo;
        args->power = bomb.getPower();
        args->x = x;
        args->y = y;
        args->pBombs = &this->_bomb;
        args->pNons = &this->_non;
        args->pSpecs = &this->_specs;
        args->BID = bomb.getBID();
        args->destroy = this->AttackDetect("bomb",x,y,ID);
        pthread_create(&pid, NULL, this->explore, args);
        BombCount += 1;
    }
    else{
        World::PlayMusic("laser");
        double x, y;
        x = ((double)_player[ID-1].getX())/80;
        y = ((double)_player[ID-1].getY())/80;
        x = (int)(x+0.5);
        y = (int)(y+0.5);
        pthread_t lase;
        laser *las = new laser();
        las->ID = ID;
        las->player = &this->_player[ID-1];
        laserAttack[ID-1] = true;
        las->destroy = this->AttackDetect("gun",x,y,ID);
        las->pNons = &this->_non;
        las->pSpecs = &this->_specs;
        pthread_create(&lase, NULL, this->giftime, las);
    }
    return;
}//人物攻击

void World::AttackGif(QPainter *painter,int ID){
    if(_player[ID-1].getAttackType() == "gun")//如果人物攻击方式为枪击，发射激光
    {
        double x, y;
        x = ((double)_player[ID-1].getX())/80;
        y = ((double)_player[ID-1].getY())/80;
        x = (int)(x+0.5);
        y = (int)(y+0.5);
        if(!laserAttack[ID-1])
            return;
        QImage lase;
        int **a = this->AttackDetect("gun",x,y,ID);
        int b;
        if(_player[ID-1].getDirection() == 1 || _player[ID-1].getDirection() == 2)
            lase.load("E:/image/laser/laservertical.png");//人物横向则加载横向激光
        else
            lase.load("E:/image/laser/laserlateral.png");//人物纵向则加载纵向激光
        switch (_player[ID-1].getDirection()) {
        case 1:
        {
            b = a[0][1] - y;
            if(a[0][0] == 0 && a[0][1] == 0)
                b = _player[ID-1].getPower();
            lase = lase.copy(0,0,80,b*80);
            painter->drawImage(_player[ID-1].getX(),_player[ID-1].getY()+120,lase);
            break;
        }//上
        case 2:
        {
            b =y - a[0][1];
            if(a[0][0] == 0 && a[0][1] == 0)
                 b = _player[ID-1].getPower();
            lase = lase.copy(0,0,80,b*80);
            painter->drawImage(_player[ID-1].getX(),_player[ID-1].getY()-(b-1)*80,lase);//纵坐标需要根据攻击效果更改
            break;
        }//下
        case 3:
        {
            b = x - a[0][0];
            if(a[0][0] == 0 && a[0][1] == 0)
                 b = _player[ID-1].getPower();
            lase = lase.copy(0,0,b*80,80);
            painter->drawImage(_player[ID-1].getX()-(b-1)*80,_player[ID-1].getY()+40,lase);//横坐标需要根据攻击效果更改
            break;
        }//左
        case 4:
        {
            b =a[0][0] - x;
            if(a[0][0] == 0 && a[0][1] == 0)
                 b = _player[ID-1].getPower();
            lase = lase.copy(0,0,b*80,80);
            painter->drawImage(_player[ID-1].getX()+80,_player[ID-1].getY()+40,lase);
            break;
        }//右
        }
        this->harm(ID,"gun");//计算伤害
        return;
    }
    else//否则产生爆炸波
    {
        for(int i = 1;i <= _under.getendY();i++)
        {
            for(int j = 1;j <= _under.getendX();j++)
            {
                int a = bombAttack[i][j];
                if(bombAttack[i][j] != 0)
                {
                    int **b = this->AttackDetect("bomb",j,i,ID);
                    int c[4];
                    this->harm(ID,"bomb");//计算伤害
                    c[0] = i - b[0][1] ;//上
                    c[1] = b[1][1] - i  ;//下
                    c[2] = j - b[2][0];//左
                    c[3] =  b[3][0] - j ;//右
                    for(int i = 0;i < 4;i++)
                    {
                        if(b[i][0] == 0 && b[i][1] == 0)
                            c[i] = _player[ID-1].getPower();

                        if(c[i] > _player[ID-1].getPower())
                            c[i] = _player[ID-1].getPower();
                    }
                    cout << c[0] <<" " << c[1]<< " "<< c[2] <<" " << c[3] <<endl;
                    //用于裁剪爆炸波图片
                    painter->drawImage(j*80+60,i*80+40,wave[0][c[3]]);//右
                    painter->drawImage(j*80-c[2]*80,i*80+40,wave[0][c[2]]);//左
                    painter->drawImage(j*80,i*80+80+20,wave[1][c[1]]);//下
                    painter->drawImage(j*80,i*80-c[0]*80+40,wave[1][c[0]]);//上
                    painter->drawImage(j*80,i*80+40,center[a-1]);
                }//检测到当前位置需要绘制爆炸波
            }
        }
    }
}//绘制动图
void* World::giftime(void *att){
    struct laser *_att;
    _att = (struct laser *)att;
    vector<Nonbarrier>* non = _att->pNons;
    vector<Specs>* specs = _att->pSpecs;
    Sleep(100);
    vector<Nonbarrier>::iterator it1;
    vector<Specs>::iterator it2;
    for(it1 = non->begin();it1 != non->end();it1++)
    {
        if(it1->getX() == _att->destroy[0][0] && it1->getY() == _att->destroy[0][1])
        {
            non->erase(it1);
            erase[_att->destroy[0][1]][_att->destroy[0][0]] = true;
            break;
        }
        if(non->end() == it1)
            break;
    }
    for(it2 = specs->begin();it2 != specs->end();it2++)
    {
        if(it2->getX() == _att->destroy[0][0] && it2->getY() == _att->destroy[0][1])
        {
            erase[_att->destroy[0][1]][_att->destroy[0][0]] = true;
            specs->erase(it2);
            break;
        }
        if(specs->end() == it2)
            break;
    }
    Sleep(100);
    laserAttack[_att->ID-1] = false;
    _att->player->setGun(false);
    delete(_att);
    return NULL;
}//设定激光动图时间,销毁物体
int ** World::AttackDetect(string type, int x, int y, int ID){
    int **detect;
    bool find[4] = {0};
    if(type == "bomb")
    {
        detect = new int*[4];
        for(int i = 0;i < 4;i++)
            detect[i] = new int[2];
        for(int i = 0;i < 4;i++)
        {
            for(int j = 0;j < 2;j++)
                detect[i][j] = 0;
        }
    }
    else
    {
        detect = new int*[1];
        detect[0] = new int[2];
        detect[0][0] = 0;
        detect[0][1] = 0;
    }
    if(type == "bomb")
    {
        int i;
        for(i = 1;i <= _player[ID-1].getPower();i++)
        {
            if((map[y-i][x]==1||y-i==0) && !find[0])
            {
                find[0] = true;
                detect[0][0] = x;
                detect[0][1] = y-i;
            }//上
            if((map[y+i][x]==1||y+i==_under.getendY()+1)&&!find[1])
            {
                find[1] = true;
                detect[1][0] = x;
                detect[1][1] = y+i;
            }//下
            if((map[y][x-i]==1||x-i==0)&&!find[2])
            {
                find[2] = true;
                detect[2][0] = x-i;
                detect[2][1] = y;
            }//左
            if((map[y][x+i]==1||x+i==_under.getendX()+1)&&!find[3])
            {
                find[3] = true;
                detect[3][0] = x+i;
                detect[3][1] = y;
            }//右
        }
    }//炸弹攻击检测四个方向
    else
    {
        int i;
        for(i = 1;i <= 5;i++)
        {
            if(_player[ID-1].getDirection() == 1 && (map[y+i][x] == 1 ||map[y+i][x] == _under.getendY()+1))
            {
                detect[0][0] = x;
                detect[0][1] = y+i;
                break;
            }//下
            if(_player[ID-1].getDirection() == 2 && (map[y-i][x] == 1 ||y-i == 0))
            {
                detect[0][0] = x;
                detect[0][1] = y-i;
                break;
            }//上
            if(_player[ID-1].getDirection() == 3 && (map[y][x-i] == 1 ||x-i== 0))
            {
                detect[0][0] = x-i;
                detect[0][1] = y;
                break;
            }//左
            if(_player[ID-1].getDirection() == 4 && (map[y][x+i] == 1 ||map[y][x+i] == _under.getendX()+1))
            {
                detect[0][0] = x+i;
                detect[0][1] = y;
                break;
            }//右
        }
    }//激光攻击检测人物朝向方向
    return detect;
}//返回攻击销毁对象的坐标信息

void World::show(QPainter *painter){
    this->_under.show(painter,i_under,i_bound);
    vector<Bomb>::iterator bomb;
    vector<Specs>::iterator specs;
    vector<Barrier>::iterator bar;
    vector<Nonbarrier>::iterator non;
    vector<Pitfall>::iterator pitfall;
    for(specs = this->_specs.begin();specs!=this->_specs.end();specs++)
    {
        int t = 0;
        if((*specs).getEffect() == "gun")
            t = 1;
        else if((*specs).getEffect() == "hammmer")
            t = 2;
        else if((*specs).getEffect() == "invul")
            t = 3;
        else if((*specs).getEffect() == "powerup")
            t = 4;
        else if((*specs).getEffect() == "pushbomb")
            t = 5;
        else if((*specs).getEffect() == "speedup")
            t = 6;
        else if((*specs).getEffect() == "limitup")
            t = 7;
        (*specs).show(painter,i_specs[t]);
    }
    for(non = this->_non.begin();non!=this->_non.end();non++)
    {
        if((*non).getID() == "2")
            (*non).show(painter,i_nonbarrier[0]);
        else
            (*non).show(painter,i_nonbarrier[1]);
    }
    for(pitfall = this->_pitfall.begin();pitfall!=this->_pitfall.end();pitfall++)
    {
        if((*pitfall).getname() == "left")
        {
            (*pitfall).show(painter,i_pitfall[0]);
            continue;
        }
        if((*pitfall).getname() == "right")
        {
            (*pitfall).show(painter,i_pitfall[1]);
            continue;
        }
            (*pitfall).show(painter,i_pitfall[2]);
    }
    for(bomb = this->_bomb.begin();bomb!=this->_bomb.end();bomb++)
    {
        (*bomb).show(painter,i_bomb);
    }
    for(bar = this->_bar.begin();bar!= this->_bar.end();bar++)
    {
        (*bar).show(painter,i_barrier);
    }
    this->_player[0].show(painter);
    this->_player[1].show(painter);
}//绘制


void World::handlemove(int ID,int direction){
    if(this->movedetect(direction,_player[ID-1],_bar)&&this->movedetect(direction,_player[ID-1],_bomb)&&this->movedetect(direction,_player[ID-1],_non))
    {
         this->_player[ID-1].move(direction);
         this->eatspecs(_player[ID-1]);
         this->pitdetect(_player[ID-1]);
    }
}//人物移动


void World::eatspecs(Player &player){
    vector<Specs>::iterator it;
    for(it = this->_specs.begin();it != this->_specs.end();it++)
    {
        if((*it).getX()*80==player.getX()&&(*it).getY()*80 == player.getY())
        {
            player.addScore();
            map[(*it).getY()][(*it).getX()] = 0;
            if((*it).getEffect() == "powerup")
                player.powerUp();
            else if((*it).getEffect() == "limitup")
                player.blimUp();
            else if((*it).getEffect() == "lifeup")
                player.lifeup();
            else if((*it).getEffect() == "gun")
                player.setGun(true);
            else if((*it).getEffect() == "invul")
                player.setInv(true);//定时关闭无敌未实现
            else if((*it).getEffect() == "speedup")
                player.speedUp();
            _specs.erase(it);

            return;
        }
    }
}//拾取道具

void World::pitdetect(Player &player){
    vector<Pitfall>::iterator it;
    for(it = this->_pitfall.begin();it != this->_pitfall.end();it++)
    {
        if((*it).getX()*80==player.getX()&&(*it).getY()*80 == player.getY())
        {
            if((*it).getname() == "right")//强制向右移动
            {
                for(int i = 1;i <= 16;i++)
                    this->handlemove(player.getID(),4);
            }
            else if((*it).getname() == "left")//强制向左移动
            {
                for(int i = 1;i <= 16;i++)
                    this->handlemove(player.getID(),3);
            }
            else if((*it).getname() == "trans")//传送
            {
                if((*it).getID()%2==1)
                    it++;
                else
                    it--;
                player.setX((*it).getX()*80);
                player.setY((*it).getY()*80);
            }
            return;
        }
    }
}//检测陷阱
void World::erasemap(){
    for(int i = 1;i <= _under.getendY();i++)
    {
        for(int j = 1;j <= _under.getendX();j++)
        {
            if(erase[i][j] == true)
            {
                map[i][j] = 0;
                erase[i][j] = false;
            }
        }
    }
}
void World::harm(int ID, string type){
    int another;
    int **att;
    if(ID == 1)
        another = 2;
    else
        another = 1;//另一玩家ID
    if(type == "gun")
    {
        double x1, y1;
        x1 = ((double)_player[ID-1].getX())/80;
        y1 = ((double)_player[ID-1].getY())/80;
        x1 = (int)(x1+0.5);
        y1 = (int)(y1+0.5);
        double x2, y2;//玩家的坐标信息
        x2 = ((double)_player[another-1].getX())/80;
        y2 = ((double)_player[another-1].getY())/80;
        x2 = (int)(x2+0.5);
        y2 = (int)(y2+0.5);//另一玩家的坐标信息
        att = this->AttackDetect("gun",x1,y1,ID);
        cout <<_player[ID-1].getDirection()  <<" " << y2 << " "  << att[0][1] <<endl;
        if(_player[ID-1].getDirection() == 1 && x1 == x2 && y2 > y1 && att[0][1] >= y2)
            this->playerdie(ID);//人物朝下攻击且另一人物在攻击范围内
        if(_player[ID-1].getDirection() == 2 &&x1 == x2 && y2 < y1 && att[0][1] <= y2)
             this->playerdie(ID);//人物朝上攻击且另一人物在攻击范围内
        if(_player[ID-1].getDirection() == 3 && y1 == y2 && x1 > x2 && x2 >= att[0][0])
             this->playerdie(ID);//人物朝左攻击且另一人物在攻击范围内
        if(_player[ID-1].getDirection() == 4 && y1 == y2 && x1 < x2 && x2 <= att[0][0])
             this->playerdie(ID);//人物朝右攻击且另一人物在攻击范围内
    }//激光枪攻击
    else
      {
          for(int i = 1;i <= 2;i++)
          {
              int p;
              if(i == 1)
                  p = 2;
              else
                  p = 1;
              int x = (_player[i-1].getX()+40)/80;
              int y = (_player[i-1].getY()+80)/80;
              att = this->AttackDetect("bomb",x,y,ID);
              if((y == att[2][1] && x >= att[2][0] && att[3][0] >= x)||(x == att[0][0] && y >= att[0][1] && att[1][1] >= y))//人物在爆炸波波及范围内
                  this->playerdie(i);
          }
      }
    /*else
    {
        for(int i = 1;i <= 2;i++)
        {
            int x = (_player[i-1].getX()+40)/80;
            int y = (_player[i-1].getY()+80)/80;
            if((y == att[2][1] && x >= att[2][0] && att[3][0] >= x)||(x == att[0][0] && y >= att[0][1] && att[1][1] >= y))//人物在爆炸波波及范围内
                this->playerdie(i);
        }
    }//炸弹爆炸*/
}//重复调用，有问题

void World::playerdie(int ID){

    _player[ID-1].addScore();
}//有问题
void World::PlayMusic(string type){
    QMediaPlayer *music = new QMediaPlayer();
    //QMessageBox::information(NULL, "game over","score: ",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(type == "bomb")
    {
        music->setMedia(QUrl::fromLocalFile("E:/image/music/blast.mp3"));
        music->play();
    }
    else if(type == "laser")
    {
        music->setMedia(QUrl::fromLocalFile("E:/image/music/laser.mp3"));
        music->play();
    }
}
/*void World::erasebomb(){
    vector<Bomb>::iterator it;
    if(blast[5][4])
        cout <<" hahahah" <<endl;
    for(int i = 1;i <= _under.getendY();i++)
    {
        for(int j = 1;j <= _under.getendX();j++)
        {
            if(blast[i][j] == true)
            {
                blast[i][j] = false;
                for(it = _bomb.begin();it != _bomb.end();it++)
                {
                    if((*it).getX() == j && (*it).getY() == i)
                    {
                        _bomb.erase(it);
                        if(_bomb.end() == it)
                            break;
                        continue;
                    }
                    it++;
                }
            }
        }
    }
}*/

void World::save(){
    string file = "E:/image/map-save.txt";
    string ch = " ";
    ofstream fout;
    vector<Specs>::iterator specs;
    vector<Barrier>::iterator bar;
    vector<Nonbarrier>::iterator non;
    vector<Pitfall>::iterator pitfall;
    fout.open(file.c_str());
    fout << mapname << ch << _under.getendX() << ch << _under.getendY() <<endl;//输出终点信息
    for(bar = _bar.begin();bar != _bar.end();bar++)
    {
        fout << "barrier" << ch << (*bar).getX() << ch << (*bar).getY() << endl;
    }
    for(non = _non.begin();non != _non.end();non++)
    {
        fout << "nonbarrier" << ch << (*non).getX() << ch << (*non).getY() << ch <<(*non).getID() <<endl;
    }
    for(specs = _specs.begin();specs != _specs.end();specs++)
    {
        fout << "specs" << ch << (*specs).getEffect() <<ch << (*specs).getX() << ch << (*specs).getY() <<endl;
    }
    for(pitfall = _pitfall.begin();pitfall != _pitfall.end();pitfall++)
    {
        fout << "pitfall" << ch <<(*pitfall).getname();
        if((*pitfall).getname() == "trans")
            fout << (*pitfall).getID();
        fout << ch << (*pitfall).getX() << ch << (*pitfall).getY() <<endl;
    }
    fout << "playerscore" <<ch << "1" << ch << _player[0].getScore() <<endl;
    fout << "playerscore" <<ch << "2" << ch << _player[1].getScore() <<endl;
}
