#include "world.h"
#include "icon.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include<QMessageBox>

using namespace std;

static vector<string> split( string str, string pattern){//字符串切割函数
    vector<string> ret;
    if(pattern.empty())
        return ret;
    size_t start=0,index=str.find_first_of(pattern,0);
    while(index!=str.npos){
        if(start!=index)
            ret.push_back(str.substr(start,index-start));
            start=index+1;
            index=str.find_first_of(pattern,start);
    }
    if(!str.substr(start).empty())
        ret.push_back(str.substr(start));
    return ret;
}

void World::initWorld(string mapFile){
    for(int i=0;i<50;i++)
        for(int j=0;j<50;j++)
            this->_map[i][j]=0;
    /*
    cout<<"1234567"<<endl;
    //TODO 下面这部分逻辑应该是读入地图文件，生成地图上的对象
    //player 5 5
    this->_player.initObj("player");
    this->_player.setPosX(5);
    this->_player.setPosY(5);

    RPGObj obj1, obj2, obj3;
    obj1.initObj("stone");
    obj1.setPosX(4);
    obj1.setPosY(3);

    obj2.initObj("stone");
    obj2.setPosX(6);
    obj2.setPosY(5);

    obj3.initObj("fruit");
    obj3.setPosX(6);
    obj3.setPosY(8);

    this->_objs.push_back(obj1);
    this->_objs.push_back(obj2);
    this->_objs.push_back(obj3);*/
    string data;
    vector<string> temp;
    ifstream in("C://work/practice/QTMap/worldmap.txt");
    while(getline(in,data)){
        temp=split(data,",");
        RPGObj ob;
        ob.initObj(temp[0]);
        ob.setPosX(atoi(temp[1].data()));
        ob.setPosY(atoi(temp[2].data()));
        this->_objs.push_back(ob);
        if(ob.canhurt()){
            for(int i=0;i<ob.getWidth();i++){
                for(int j=0;j<ob.getHeight();j++){
                    this->_map[ob.getPosX()+i][ob.getPosY()+j]=5;
                }
            }
        }
        else if(!(ob.canEat()||ob.canCover())){
            for(int i=0;i<ob.getWidth();i++){
                for(int j=0;j<ob.getHeight();j++){
                    this->_map[ob.getPosX()+i][ob.getPosY()+j]=1;
                }
            }
        }else if((!ob.canEat())&&ob.canCover()){
            for(int i=0;i<ob.getWidth();i++){
                for(int j=0;j<ob.getHeight();j++){
                    this->_map[ob.getPosX()+i][ob.getPosY()+j]=2;
                }
            }
        }else if(ob.canEat()&&(!ob.canCover())){
            for(int i=0;i<ob.getWidth();i++){
                for(int j=0;j<ob.getHeight();j++){
                    this->_map[ob.getPosX()+i][ob.getPosY()+j]=3;
                }
            }
        }else if(ob.canEat()&&ob.canCover()){
            for(int i=0;i<ob.getWidth();i++){
                for(int j=0;j<ob.getHeight();j++){
                    this->_map[ob.getPosX()+i][ob.getPosY()+j]=4;
                }
            }
        }
        /*
        map < string,vector<RPGObj> >::iterator iter;
        string s="_";
        iter=this->_map.find(temp[1].data()+s+temp[2].data());
        vector<RPGObj> obb;
        if(iter==this->_map.end()){
            this->_map.insert(pair< string,vector<RPGObj> > (temp[1].data()+s+temp[2].data(),obb));
        }
        this->_map[temp[1].data()+s+temp[2].data()].push_back(ob);
        cout<<temp[1].data()+s+temp[2].data()<<endl;*/
    }
    this->_player.initObj("player");
    this->_player.setPosX(7);
    this->_player.setPosY(8);
    for(int i=0;i<32;i++){
        for(int j=0;j<40;j++){
            cout<<this->_map[i][j];
        }
        cout<<endl;
    }
}


void World::show(QPainter * painter){
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        (*it).show(painter);
    }
    //cout<<"HH"<<_objs.size()<<endl;
    this->_player.show(painter);
}

string to_Str(int n){
    ostringstream stream;
    stream<<n;
    return stream.str();
}

void World::removeRPGObj(int x,int y){
    cout<<"in"<<endl;
    vector<RPGObj>::iterator it;
    for(it=this->_objs.begin();it!=this->_objs.end();it++){
        while( it->getPosX()<=x && it->getPosX()+it->getWidth()>=x
               && it->getPosY()<=y && it->getPosY() >=y &&
               it->canEat()==true){
            for(int i=0;i<it->getWidth();i++)
                for(int j=0;j<it->getHeight();j++)
                    this->_map[it->getPosX()+i][it->getPosY()+j]=0;
            it=this->_objs.erase(it);
            if(it==this->_objs.end())
                break;
        }
        if(it==this->_objs.end())
            break;
    }
}

void World::handlePlayerMove(int direction, int steps){
    int true_X=this->_player.getPosX();
    int true_Y=this->_player.getPosY()+1;
    if(direction==1){
        if(this->_map[true_X][true_Y-1]==5){
            QMessageBox *msgBox;
                msgBox = new QMessageBox("Game Over",       ///--这里是设置消息框标题
                    "Game Over",                       ///--这里是设置消息框显示的内容
                    QMessageBox::Critical,                          ///--这里是在消息框显示的图标
                    QMessageBox::Ok | QMessageBox::Default,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Cancel | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);                                                     ///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮

                msgBox->show();

        }
        else if(this->_map[true_X][true_Y-1]==3||this->_map[true_X][true_Y-1]==4){
            removeRPGObj(true_X,true_Y-1);
        }
        else if(this->_map[true_X][true_Y-1]==2){
        }
        else if(this->_map[true_X][true_Y-1]!=0 || true_Y==0)
            return;
    }
    else if(direction==2){
        if(this->_map[true_X][true_Y+1]==5){
            QMessageBox *msgBox;
                msgBox = new QMessageBox("Game Over",       ///--这里是设置消息框标题
                    "Game Over",                       ///--这里是设置消息框显示的内容
                    QMessageBox::Critical,                          ///--这里是在消息框显示的图标
                    QMessageBox::Ok | QMessageBox::Default,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Cancel | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);                                                     ///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮

                msgBox->show();
        }
        else if(this->_map[true_X][true_Y+1]==3||this->_map[true_X][true_Y+1]==4){
            removeRPGObj(true_X,true_Y+1);
        }
        else if(this->_map[true_X][true_Y+1]==2){
        }
        else if(this->_map[true_X][true_Y+1]!=0 || true_Y==31){
            return;
        }
    }
    else if(direction==3){
        if(this->_map[true_X-1][true_Y]==5){
            QMessageBox *msgBox;
                msgBox = new QMessageBox("Game Over",       ///--这里是设置消息框标题
                    "Game Over",                       ///--这里是设置消息框显示的内容
                    QMessageBox::Critical,                          ///--这里是在消息框显示的图标
                    QMessageBox::Ok | QMessageBox::Default,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Cancel | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);                                                     ///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮

                msgBox->show();
        }
        else if(this->_map[true_X-1][true_Y]==3||this->_map[true_X-1][true_Y]==4){
            removeRPGObj(true_X-1,true_Y);
        }
        else if(this->_map[true_X-1][true_Y]==2){
        }
        else if(this->_map[true_X-1][true_Y]!=0 || true_X==0){
            return;
        }
    }
    else if(direction==4){
        if(this->_map[true_X+1][true_Y]==5){
            QMessageBox *msgBox;
                msgBox = new QMessageBox("Game Over",       ///--这里是设置消息框标题
                    "Game Over",                       ///--这里是设置消息框显示的内容
                    QMessageBox::Critical,                          ///--这里是在消息框显示的图标
                    QMessageBox::Ok | QMessageBox::Default,     ///---这里是显示消息框上的按钮情况
                    QMessageBox::Cancel | QMessageBox::Escape,  ///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
                    0);                                                     ///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮

                msgBox->show();
        }
        else if(this->_map[true_X+1][true_Y]==3||this->_map[true_X+1][true_Y]==4){
            removeRPGObj(true_X+1,true_Y);
        }
        else if(this->_map[true_X+1][true_Y]==2){
        }
        else if(this->_map[true_X+1][true_Y]!=0 || true_X==39){
            return;
        }
    }
    this->_player.move(direction, steps);
}

