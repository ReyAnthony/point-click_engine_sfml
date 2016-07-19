//
// Created by Jiiva on 112/07/2016.
//

#ifndef CHECKCOLLIDER_COLLIDER_H
#define CHECKCOLLIDER_COLLIDER_H


class Collider {

public:
    Collider();
    Collider(int width, int height, int abcisse, int orderly);

    bool isInside(int x ,int y) {

        int _x = this->x;
        int _y = this->y;

        return (x > _x && x < _x + width ) && (y > _y && y < _y + height);

    }
    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    int getAbcisse() const {
        return x;
    }

    int getOrderly() const {
        return y;
    }

private:
    int x;
    int y;
    int height;
    int width;
};


#endif //CHECKCOLLIDER_COLLIDER_H
