//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_ACTIONPANEL_HPP
#define SFML_TEST_ACTIONPANEL_HPP

#include <list>
#include "../../exceptions/Exception.hpp"
#include "Button.hpp"
#include "../../conf/ConfReader.hpp"

class ActionPanel : public sf::Drawable {

public:

    ActionPanel(TxtConfReader& configuration){

        buttons.push_back(new Button(GOTO, "GotoButton", 0, 0, configuration.getButtonPath(GOTO)));
        buttons.push_back(new Button(GRAB, "GrabButton", 256, 0, configuration.getButtonPath(GRAB)));
        buttons.push_back(new Button(SEE, "SeeButton", 256 * 2, 0, configuration.getButtonPath(SEE)));
        buttons.push_back(new Button(TALK, "TalkButton", 256 * 3, 0, configuration.getButtonPath(TALK)));
        buttons.push_back(new Button(USE, "UseButton", 256 * 4, 0, configuration.getButtonPath(USE)));

        current_status = NOOP;
    }

    GUIActionsType doAction(sf::Event& event, sf::RenderTarget& renderTarget) {

        auto actionType = NOOP;

        for(auto b : buttons){

            actionType = b->doAction(event, renderTarget);

            if(actionType != NOOP){
                current_status = actionType;
                std::cout << *b;
                break;
            }
        }

        return current_status;
    }

    GUIActionsType getActionType(){
        return current_status;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const{
        for(sf::Drawable* b : buttons){
            target.draw(*b, renderStates);
        }
    }

    std::list<Button*> buttons;
    GUIActionsType current_status;
};


#endif //SFML_TEST_ACTIONPANEL_HPP
