#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMultimedia/QMediaPlayer>
#include<QUrl>
#include<QTimer>
#include<QImage>
#include<QIcon>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include <pthread.h>
#include <windows.h>
using namespace std;

int MainWindow::start = 0;
int MainWindow::mode = 0;
int m = 2,s = 59;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m = 1;
    s = 59;
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(on_pushButton_1_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    pthread_t time;
    int a[2];
    a[1] = m;
    a[2] = s;
     pthread_create(&time, NULL, this->addtime, a);
//    this->resize( QSize( 800, 600 ));
    startimage.load("E:/image/start.png");
    string file = "E:/image/music/Luv Letter.mp3";
    music_list.push_back(file);
    string file1 = "E:/image/music/Flower Dance.mp3";
    music_list.push_back(file1);
    playmusic=new QMediaPlayer();
    current_music=0;
    playmusic->setMedia(QUrl::fromLocalFile((music_list[current_music].c_str())));
    playmusic->play();
    this->resize( QSize( this->_world.getendX()*80+480, this->_world.getendY()*80+220 ));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(100);

    /*QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(addtime()));
    timer2->start(1000);*/
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(addtime();));
    timer2->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void* MainWindow::addtime(void *a){
    for(int i = 1;i <= 59;i++)
    {
        Sleep(1000);
        s--;
    }
    s = 59;
    m--;
    for(int i = 1;i <= 59;i++)
    {
        Sleep(1000);
        s--;
    }
    s = 59;
    m--;
    for(int i = 1;i <= 59;i++)
    {
        Sleep(1000);
        s--;
    }
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    if(s == 0 && m == 0)
    {
        ostringstream os1,os2,os3,os4;
        os1 << this->_world._player[0].getScore();
        string a=os1.str();
        a = "player1分数是 : "+a;
        os2 << this->_world._player[1].getScore();
        string b=os2.str();
        b = "player2分数是 : "+b;
        QFont font;
        font.setFamily("宋体");
        font.setPointSize(50);
        painter->setFont(font);
        painter->setPen(Qt::green);
        painter->drawText(500,200,a.c_str());
        painter->drawText(500,300,b.c_str());
        return;
    }
    if(start)
    {
        this->_world.show(painter);
        this->_world.AttackGif(painter,1);
        this->_world.AttackGif(painter,2);
        this->_world.erasemap();
        ostringstream os1,os2,os3,os4;
        os1 << this->_world._player[0].getScore();
        string a=os1.str();
        a = "player1分数是 : "+a;
        os2 << this->_world._player[1].getScore();
        string b=os2.str();
        b = "player2分数是 : "+b;
        QFont font;
        font.setFamily("宋体");
        font.setPointSize(20);
        painter->setFont(font);
        painter->setPen(Qt::green);
        painter->drawText(1500,200,a.c_str());
        painter->drawText(1500,300,b.c_str());
        string c;
        os3 << m;
        os4 << s;
        c ="time:" + os3.str() + ":" + os4.str();
        painter->drawText(1500,100,c.c_str());
    }
    else{
        painter->drawImage(0,0,startimage);
    }

    painter->end();
    delete painter;
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    QPainter *painter;
    painter = new QPainter();
    painter->begin(this);
    if(e->key() == Qt::Key_A)
    {
        this->_world.handlemove(1,3);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_world.handlemove(1,4);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_world.handlemove(1,2);
    }
    else if(e->key() == Qt::Key_S)
    {
        this->_world.handlemove(1,1);
    }
    else if(e->key() == Qt::Key_Space)
    {
        this->_world.attack(1);
    }

    if(e->key() == Qt::Key_Down){
        this->_world.handlemove(2,1);
    }
    else if(e->key() == Qt::Key_Up)
    {
        this->_world.handlemove(2,2);
    }
    else if(e->key() == Qt::Key_Left)
    {
        this->_world.handlemove(2,3);
    }
    else if(e->key() == Qt::Key_Right)
    {
        this->_world.handlemove(2,4);
    }
    else if(e->key() == Qt::Key_Shift)
    {
        this->_world.attack(2);
    }
    else if(e->key() == Qt::Key_Escape)
    {
        this->_world.save();
        exit(0);
    }

    this->repaint();
}
void MainWindow::pause_music(){
    this->playmusic->pause();
}
void MainWindow::stop_music(){
    this->playmusic->stop();
}
void MainWindow::play_music(){
    this->playmusic->play();
}
void MainWindow::switch_music(){
    current_music+=1;
    current_music%music_list.size();
    playmusic->setMedia(QUrl::fromLocalFile((music_list[current_music].c_str())));
}

void MainWindow::on_pushButton_1_clicked()
{
    start = true;
    mode = 1;
    _world.initWorld();
    delete(ui->pushButton_1);
    delete(ui->pushButton_2);
    delete(ui->pushButton);
}

void MainWindow::on_pushButton_2_clicked()
{
    start = true;
    mode = 2;
    _world.initWorld();
    delete(ui->pushButton_1);
    delete(ui->pushButton_2);
    delete(ui->pushButton);
}

void MainWindow::on_pushButton_clicked()
{
    start = true;
    _world.read();
    _world.initWorld();
    delete(ui->pushButton_1);
    delete(ui->pushButton_2);
    delete(ui->pushButton);
}
