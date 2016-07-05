//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_TALKACTION_HPP
#define SFML_TEST_TALKACTION_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include "../AbstractAction.hpp"

class TalkAction : public AbstractAction{
private:
    std::vector<std::string> sentences;
public:

    const std::vector<std::string> getSentences() const {
        return sentences;
    }

    TalkAction(std::vector<std::string> sentences) : sentences(sentences) {

        this->setActionType(TALK);
    }

    TalkAction(){
        this->setActionType(TALK);

    }
};


#endif //SFML_TEST_TALKACTION_HPP
