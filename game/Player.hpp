//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_PLAYER_HPP
#define SFML_TEST_PLAYER_HPP


#include <SFML/Window/Keyboard.hpp>
#include "../events/Observer.hpp"
#include "Object.hpp"

class Player : public Object {

public:

    Player(std::string name,
           int pos_x,
           int pos_y,
           std::string texture_file,
           int frames = 1,
           int ms_beetwen_frames = 0)
            : Object(name, pos_x, pos_y, texture_file, frames, ms_beetwen_frames, 0), empty_action(NOOP)
    {
    }

    Action & doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) override;
    void update(sf::Time& deltaTime) override;
    Action empty_action;

};


#endif //SFML_TEST_PLAYER_HPP
