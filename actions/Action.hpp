//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_ACTIONS_HPP
#define SFML_TEST_ACTIONS_HPP


class Action {

public:
    enum PossibleActions {
        TALK,
        USE,
        NOOP
    };

    Action(PossibleActions type){
        p = type;
    }

    PossibleActions getActionType(){
        return p;
    }

private:

    PossibleActions p = PossibleActions::TALK;

};


#endif //SFML_TEST_ACTIONS_HPP
