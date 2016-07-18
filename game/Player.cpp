//
// Created by Anthony REY on 30/06/2016.
//

#include "Player.hpp"

Action & Player::doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) {

    if(event.type == event.KeyPressed) {

        auto current_pos_x = getPosX();
        auto current_pos_y = getPosY();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            setPosX(current_pos_x - 10);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            setPosX(current_pos_x + 10);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            setPosY(current_pos_y - 10);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            setPosY(current_pos_y + 10);
    }

}