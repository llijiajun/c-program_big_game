#include"score.h"

void Score::add(int s){
    this->score+=s;
}

void Score::mins(int s){
    this->score-=s;
}

int Score::getScore(){
    return score;
}
