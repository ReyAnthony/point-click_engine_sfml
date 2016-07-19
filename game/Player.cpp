//
// Created by Anthony REY on 30/06/2016.
//

#include "Player.hpp"

Action & Player::doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) {

    return empty_action;
}

void Player::update(sf::Time& deltaTime){

    auto current_pos_x = getPosX();
    auto current_pos_y = getPosY();

    positionBeforeUpdate = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        setPosX(current_pos_x - 5);
        current_direction = W_LEFT;
        animated = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setPosX(current_pos_x + 5);
        current_direction = W_RIGHT;
        animated = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        setPosY(current_pos_y - 5);
        current_direction = W_UP;
        animated = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        setPosY(current_pos_y + 5);
        current_direction = W_DOWN;
        animated = true;
    }
    else
        animated = false;

    updateCollider();

    int width = texture.getSize().x / (frames * 4); // eg : 3 frames * 4 directions
    int height = texture.getSize().y;

    if(animated){

        elapsed_time += deltaTime;

        if(elapsed_time.asMilliseconds() > ms_beetwen_frames){

            if(current_frame >= frames - 1)
                current_frame = 0;
            else
                current_frame++;

            int start_x = (frames * width * current_direction) + current_frame * width;

            this->sprite.setTextureRect(sf::IntRect(start_x, 0, width, height));
            elapsed_time = sf::Time::Zero;
        }
    }
    else
        this->sprite.setTextureRect(sf::IntRect( (frames * width * current_direction) , 0, width, height));

}

void Player::revertToPositionBeforeUpdate() {

    sprite.setPosition(positionBeforeUpdate);
}

void Player::updateCollider() {

    int x_max = texture.getSize().x / (frames * 4); //directions
    int y_max = texture.getSize().y;

    collider = Collider(x_max, 10,
                        sprite.getPosition().x,
                        sprite.getPosition().y
                        + sprite.getTexture()->getSize().y);
}