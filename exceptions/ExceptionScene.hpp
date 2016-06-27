//
// Created by Anthony REY on 26/06/2016.
//

#ifndef SFML_TEST_EXCEPTIONSCENE_HPP
#define SFML_TEST_EXCEPTIONSCENE_HPP


#include "../game/Scene.hpp"
#include "../exceptions/Exception.hpp"

class ExceptionScene : public Scene {

public:

    ExceptionScene(std::string default_font_path, Exception& exception);
    ExceptionScene(const ExceptionScene& ref);
    ExceptionScene & operator=(const ExceptionScene& ref);

private:

    void draw(sf::RenderTarget& target, sf::RenderStates) const;

    sf::Text text;
    sf::Font font;
};


#endif //SFML_TEST_EXCEPTIONSCENE_HPP
