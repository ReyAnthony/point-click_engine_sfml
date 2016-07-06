//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_SEEACTION_HPP
#define SFML_TEST_SEEACTION_HPP


#include "../AbstractAction.hpp"
#include "TalkAction.hpp"

class SeeAction : public TalkAction {

public:
    SeeAction(std::vector<std::string> sentences) : TalkAction(sentences) {
        this->setActionType(SEE);
    }

    SeeAction() {
        this->setActionType(SEE);
    }
};


#endif //SFML_TEST_SEEACTION_HPP
