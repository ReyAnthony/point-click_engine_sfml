//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_ABSTRACTACTION_HPP
#define SFML_TEST_ABSTRACTACTION_HPP


#include "../events/GUIActionType.hpp"

class Action {

public:

    Action(GUIActionsType actionType){

        this->actionsType = actionType;
    }

    Action(GUIActionsType actionType, std::vector<std::string> sentences) : sentences(sentences) {
            this->setActionType(TALK);
    }

    GUIActionsType getActionType(){
        return this->actionsType;
    }

    void setActionType(GUIActionsType actionsType){
        this->actionsType = actionsType;
    }

    const std::vector<std::string> getSentences() const {
        return sentences;
    }

private:
    std::vector<std::string> sentences;
    GUIActionsType actionsType = NOOP;

};


#endif //SFML_TEST_ABSTRACTACTION_HPP
