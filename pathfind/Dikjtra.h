//
// Created by Jiiva on 12/07/2016.
//

#ifndef CHECKCOLLIDER_DIKJTRA_H
#define CHECKCOLLIDER_DIKJTRA_H

#include <list>
#include <iostream>
#include <c++/vector>
#include "Collider.h"
#include "Tuple.h"

class Dikjtra {
public:

    Dikjtra(std::list<Collider *> &colliders, int line_count, int column_count, int grid_ratio);

    int getGrid_ratio() const {
        return grid_ratio;
    }

    void setGrid_ratio(int grid_ratio) {
        grid_ratio = grid_ratio;
    }

    std::list <Tuple> shortDistance(int **grid,Tuple source,Tuple destination) {

        int value;
        for (int j = 0; j <(this->line_count) ; ++j) {
            for (int i = 0; i <(this->column_count) ; ++i) {
                if (j == source.getX()&& i == source.getY()){
                    value = grid[source.getX()][source.getY()];
                    if(value >1 || value <= 0){
                        // j'ai toujour des probleme au niveau de dijktra
                        //je suis dsl;
                    }
                }
            }
        }


    }
    ~Dikjtra();

private:
    void setUpWeights();

    std::list <Collider*> &colliders;
    int **grid;
    int line_count;
    int column_count;
    int default_node_weight =1;
    int grid_ratio;
};

#endif //CHECKCOLLIDER_DIKJTRA_H
