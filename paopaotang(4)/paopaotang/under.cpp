#include "under.h"
#include<QPainter>
#include<QImage>
#include<iostream>
using namespace std;
int Under::size = 80;
Under::Under()
{
    this->_startX = 0;
    this->_startY = 0;
}

void Under::show(QPainter *painter, QImage under, QImage bound){
    for(int i = 0;i <= _endX+1;i++)
    {
        for(int j = 0;j <=_endY+1;j++)
        {
                painter->drawImage(i*size,j*size+40,under);
                if(i == 0 || j == 0||i == _endX+1 || j == _endY+1)
                    painter->drawImage(i*size,j*size+40,bound);
        }
    }

}
