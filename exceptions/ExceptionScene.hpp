//
// Created by Anthony REY on 26/06/2016.
//

#ifndef SFML_TEST_EXCEPTIONSCENE_HPP
#define SFML_TEST_EXCEPTIONSCENE_HPP


#include "../exceptions/Exception.hpp"
#include "../game/AbstractScene.hpp"

class ExceptionScene : public AbstractScene {

public:

    ExceptionScene(std::string default_font_path, Exception& exception);
    ExceptionScene(const ExceptionScene& ref);
    ExceptionScene & operator=(const ExceptionScene& ref);

    void update(sf::Time& deltaTime, sf::RenderWindow& window);

private:

    void draw(sf::RenderTarget& target, sf::RenderStates) const;

    sf::Text text;
    sf::Font font;
};


#endif //SFML_TEST_EXCEPTIONSCENE_HPP
