//
// Created by Jiiva on 11/07/2016.
//

#include "Collider.h"

Collider::Collider() {
    this->x=0;
    this->y=0;
    this->height=0;
    this->width=0;
};

Collider::Collider(int width, int height, int abcisse, int orderly) {
    this->width = width;
    this->height = height;
    this->y =  orderly;
    this->x = abcisse;
};

