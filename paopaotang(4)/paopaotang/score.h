#ifndef SCORE
#define SCORE

class Score{
private:
    int score;
public:
    Score(){
        score=0;
    }
    void add(int s);
    void mins(int s);
    void set(int s){score = s;}
    int getScore();
};

#endif // SCORE
