#include "nonbarrier.h"
#include<QImage>
#include<QPainter>
using namespace std;
void Nonbarrier::show(QPainter *painter, QImage non){
    painter->drawImage(PosX*size,PosY*size+40,non);
}
