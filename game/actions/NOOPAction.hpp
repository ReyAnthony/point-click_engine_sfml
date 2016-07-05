//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_NOOPACTION_HPP
#define SFML_TEST_NOOPACTION_HPP


#include "../AbstractAction.hpp"

class NoopAction : public AbstractAction{
private:

public:
    NoopAction(){
        this->setActionType(NOOP);
    }

};


#endif //SFML_TEST_NOOPACTION_HPP
