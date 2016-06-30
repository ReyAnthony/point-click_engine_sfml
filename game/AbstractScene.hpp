//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_ABSTRACTSCENE_HPP
#define SFML_TEST_ABSTRACTSCENE_HPP

#include <SFML/Graphics.hpp>
#include "../events/Observer.hpp"

class AbstractScene : public sf::Drawable, public Observer<sf::Event> {

public:
    virtual void update(sf::Time& deltaTime,  sf::RenderWindow& window) = 0;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const = 0;
};


#endif //SFML_TEST_ABSTRACTSCENE_HPP
