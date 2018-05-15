#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"
#include<QMessageBox>
#include <map>
#include <iostream>

using namespace std;

static int CLOSE_WINDOWS=0;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);

    //init game world
    _game.initWorld("");//TODO 应该是输入有效的地图文件
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    /*QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;*/
    Q_UNUSED(e);
    QPainter painter(this);
    /*QImage img;
    img.load("C://work/practice/QTMap/TileB.png");
    painter.drawImage(0,0,img);*/
    this->_game.show(&painter);
}

void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
       // cout<<"A"<<endl;
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        //cout<<"D"<<endl;
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        //cout<<"W"<<endl;
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
        //cout<<"S"<<endl;
    }
    this->repaint();
      //  clo->accept();
}
