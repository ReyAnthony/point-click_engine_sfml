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

    Action(std::vector<std::string> sentences) : sentences(sentences) {
            this->setActionType(TALK);
    }

    Action(std::string new_level)  {
        this->setActionType(USE);
        this->new_level = new_level;
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


    std::string getNewLevel() const {
        return new_level;
    }


private:
    std::string new_level;
    std::vector<std::string> sentences;
    GUIActionsType actionsType = NOOP;

};


#endif //SFML_TEST_ABSTRACTACTION_HPP
