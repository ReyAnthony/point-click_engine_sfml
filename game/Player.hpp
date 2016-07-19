//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_PLAYER_HPP
#define SFML_TEST_PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include "../events/Observer.hpp"
#include "Object.hpp"

class Player : public Object {

    enum SpriteDirections
    {
        W_DOWN = 0,
        W_UP = 1,
        W_RIGHT = 2,
        W_LEFT = 3,
    };

public:

    Player(std::string name,
           int pos_x,
           int pos_y,
           std::string texture_file,
           int frames = 1,
           int ms_beetwen_frames = 0);

    Player & operator=(const Player& ref){
        Object::operator=(ref);
        positionBeforeUpdate = ref.positionBeforeUpdate;
        current_direction = ref.current_direction;
        return *this;
    }

    Player(const Player& ref);

    Action & doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) override;
    void update(sf::Time& deltaTime) override;
    Action empty_action;

    SpriteDirections current_direction = W_DOWN;
    void revertToPositionBeforeUpdate();

private:
    void updateCollider();
    sf::Vector2f positionBeforeUpdate;

};


#endif //SFML_TEST_PLAYER_HPP
