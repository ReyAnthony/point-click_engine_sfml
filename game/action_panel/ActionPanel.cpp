//
// Created by Anthony REY on 03/07/2016.
//

#include "ActionPanel.hpp"

ActionPanel::ActionPanel(TxtConfReader& configuration) {

    buttons.push_back(new Button(GOTO, "GotoButton", 0, 0, configuration.getButtonPath(GOTO)));
    buttons.push_back(new Button(GRAB, "GrabButton", 256, 0, configuration.getButtonPath(GRAB)));
    buttons.push_back(new Button(SEE, "SeeButton", 256 * 2, 0, configuration.getButtonPath(SEE)));
    buttons.push_back(new Button(TALK, "TalkButton", 256 * 3, 0, configuration.getButtonPath(TALK)));
    buttons.push_back(new Button(USE, "UseButton", 256 * 4, 0, configuration.getButtonPath(USE)));

    current_status = NOOP;
}

GUIActionsType ActionPanel::doAction(sf::Event& event, sf::RenderTarget& renderTarget) {

    auto actionType = NOOP;

    for(auto b : buttons){

        actionType = b->doAction(event, renderTarget);

        if(actionType != NOOP){
            current_status = actionType;
            break;
        }
    }

    return current_status;
}

GUIActionsType ActionPanel::getActionType() {
    return current_status;
}

void  ActionPanel::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const {
    for(sf::Drawable* b : buttons){
        target.draw(*b, renderStates);
    }
}