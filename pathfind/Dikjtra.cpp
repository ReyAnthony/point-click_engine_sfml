//
// Created by Jiiva on 12/07/2016.
//

#include "Dikjtra.h"


Dikjtra::Dikjtra(std::list<Collider *> &colliders, int line_count, int column_count, int grid_ratio) : colliders(colliders) {

    this->line_count = line_count/grid_ratio;
    this->column_count = column_count/grid_ratio;

    grid = new int*[this->line_count];
    for(int i = 0; i < (this->line_count); ++i)
        grid[i] = new int[this->column_count];

    for (int j = 0; j <(this->line_count) ; ++j) {
        for (int i = 0; i <(this->column_count) ; ++i) {
            grid[j][i] = 1;
        }
    }
    this->grid_ratio = grid_ratio;

    setUpWeights();
}

Dikjtra::~Dikjtra() {
    for (int i = 0; i < line_count ; ++i){
        delete [] grid[i];
    }
}

void Dikjtra::setUpWeights() {
    if (this->colliders.empty()) {
        std::cout << "la liste est vide" << std::endl;
    }
    else {

        for (auto collider : colliders) {

            for (int i = 0; i < line_count; ++i) {
                for (int j = 0; j < column_count; ++j) {

                    if (collider->isInside(j*grid_ratio, i*grid_ratio)) {
                        grid[i][j] = INT_MAX;
                        std::cout<<"je suis ici"<<std::endl;
                    }
                }
            }
        }
    }
   /* for (int i = 0; i < line_count; ++i) {
        for (int j = 0; j < column_count; ++j) {
            std::cout << grid[i][j];
        }
        std::cout<<std::endl;
    }*/
}