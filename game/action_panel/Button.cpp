//
// Created by Anthony REY on 03/07/2016.
//

#include "Button.hpp"

Button::Button(GUIActionsType actionType, std::string name, int x, int y, std::string sprite_file ) : Object(name, x, y, sprite_file),
                                                                                                      actionType(actionType) {}

Action &Button::doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) {

    throw Exception("doAction is not implemented for Buttons");
}

GUIActionsType Button::doAction(sf::Event& event, sf::RenderTarget& renderTarget) {

    if(isClicked(event, renderTarget)){
        return actionType;
    }

    return NOOP;

}



bool Button::isClicked(sf::Event& event, sf::RenderTarget& renderTarget) {
    if(event.type == sf::Event::MouseButtonPressed){

        auto x = event.mouseButton.x;
        auto y = event.mouseButton.y;

        sf::Vector2f pixel_position(x, y);

        if (sprite.getGlobalBounds().contains(pixel_position)) {
            return true;
        }
    }
    return false;
}