//
// Created by Anthony REY on 29/06/2016.
//

#ifndef SFML_TEST_USERACTION_HPP
#define SFML_TEST_USERACTION_HPP

#include "../game/GameScene.hpp"

class UserAction {

    void execute(int mouse_x, int mouse_y){

    }

    bool isRunning(){
        return false;
    }

    GameScene & scene;
};


#endif //SFML_TEST_USERACTION_HPP
