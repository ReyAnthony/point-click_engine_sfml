//
// Created by Anthony REY on 18/07/2016.
//
#include "Action.hpp"

Action::Action(GUIActionsType actionType) {

    this->actionsType = actionType;
}

Action::Action(std::vector<std::string> sentences) : sentences(sentences) {
    this->setActionType(TALK);
}

Action::Action(std::string new_level, bool need_in_inventory) {
    this->setActionType(USE);
    this->new_level = new_level;
    this->need_in_inventory = need_in_inventory;
}

GUIActionsType Action::getActionType() {
    return this->actionsType;
}

void Action::setActionType(GUIActionsType actionsType) {
    this->actionsType = actionsType;
}

std::string Action::getNewLevel() const {
    return new_level;
}

bool Action::isNeededInInventory() {
    return need_in_inventory;
}

Action::Action(const Action& other ) {
    this->new_level = other.new_level;
    this->sentences = other.sentences;
    this->actionsType = other.actionsType;
    this->need_in_inventory = other.need_in_inventory;
}

Action &Action::operator=(const Action& other) {

    this->new_level = other.new_level;
    this->sentences = other.sentences;
    this->actionsType = other.actionsType;
    this->need_in_inventory = other.need_in_inventory;

    return *this;
}