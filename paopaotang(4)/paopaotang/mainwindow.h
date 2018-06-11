#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QImage>
#include<QPainter>
#include<QKeyEvent>
#include<QtMultimedia/QMediaPlayer>
#include<QUrl>
#include"world.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void pause_music();
    void stop_music();
    void play_music();
    void switch_music();
    static  void *addtime(void *a);
protected:

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *playmusic;
    vector<string> music_list;
    int current_music;
    static int start;
    static int mode;//游戏模式,1表示遭遇战,2表示计时战;
    World _world;
    QImage startimage;
};

#endif // MAINWINDOW_H
