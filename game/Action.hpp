//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_ABSTRACTACTION_HPP
#define SFML_TEST_ABSTRACTACTION_HPP


#include <iosfwd>
#include <vector>
#include <string>
#include "../events/GUIActionType.hpp"

class Action {

public:

    Action(GUIActionsType actionType);
    Action(const Action& other );
    Action & operator=(const Action& other);
    Action(std::vector<std::string> sentences);
    Action(std::string new_level, bool need_in_inventory = false);
    GUIActionsType getActionType();
    void setActionType(GUIActionsType actionsType);

    const std::vector<std::string> getSentences() const {
        return sentences;
    }

    std::string getNewLevel() const;
    bool isNeededInInventory();


private:
    std::string new_level;
    std::vector<std::string> sentences;
    GUIActionsType actionsType = NOOP;
    bool need_in_inventory;
};


#endif //SFML_TEST_ABSTRACTACTION_HPP
