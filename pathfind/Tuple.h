//
// Created by Jiiva on 14/07/2016.
//

#ifndef CHECKCOLLIDER_TUPLE_H
#define CHECKCOLLIDER_TUPLE_H


class Tuple {

private:
    int x;
    int y;

public:


    Tuple(int y, int x){
        this->x = x;
        this->y = y;
    }

    Tuple getUp(Tuple t){
        t.y = t.y-1;
        return t;
    }

    Tuple getDown(Tuple t){
        t.y = t.y+1;
        return t;
    }

    Tuple getRight(Tuple t){
        t.x = t.x+1;
        return t;
    }

    Tuple getLeft(Tuple t){
        t.x = t.x-1;
        return t;
    }
    Tuple getUpReight(Tuple t){
        t.x = t.x+1;
        t.y = t.y-1;
        return t;
    }
    Tuple getUpLeft(Tuple t){
        t.x = t.x-1;
        t.y = t.y-1;
        return t;
    }
    Tuple getDownLeft(Tuple t){
        t.x = t.x-1;
        t.y = t.y+1;
        return t;
    }
    Tuple getDownReight(Tuple t){
        t.x = t.x+1;
        t.y = t.y+1;
        return t;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }





};


#endif //CHECKCOLLIDER_TUPLE_H
