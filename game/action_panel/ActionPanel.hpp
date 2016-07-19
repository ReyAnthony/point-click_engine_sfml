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

    ActionPanel(TxtConfReader& configuration);
    GUIActionsType doAction(sf::Event& event, sf::RenderTarget& renderTarget);
    GUIActionsType getActionType();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const;

    std::list<Button*> buttons;
    GUIActionsType current_status;
};


#endif //SFML_TEST_ACTIONPANEL_HPP
