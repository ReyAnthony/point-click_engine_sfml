//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_ABSTRACTACTION_HPP
#define SFML_TEST_ABSTRACTACTION_HPP


#include "../events/GUIActionType.hpp"

class AbstractAction {

private:
    GUIActionsType actionsType = NOOP;

protected:
    AbstractAction(){

    }

public:
    GUIActionsType getActionType(){
        return this->actionsType;
    }

    void setActionType(GUIActionsType actionsType){
        this->actionsType = actionsType;
    }

};


#endif //SFML_TEST_ABSTRACTACTION_HPP
