//
// Created by Anthony REY on 26/06/2016.
//

#ifndef SFML_TEST_EXCEPTIONSCENE_HPP
#define SFML_TEST_EXCEPTIONSCENE_HPP


#include "../game/Scene.hpp"
#include "../exceptions/Exception.hpp"

class ExceptionScene : public Scene {

public:

    ExceptionScene(std::string default_font_path, Exception& exception) : Scene(){

        font.loadFromFile(default_font_path);

        text.setString("There was an issue with the configuration ! \n" + exception.getErrorMessage());
        text.setCharacterSize(20);
        text.setPosition(0,0);
        text.setColor(sf::Color::Red);
        text.setFont(font);
    }

    ExceptionScene(const ExceptionScene& ref) : Scene(ref)
    {
        text.setString(ref.text.getString());
        text.setCharacterSize(ref.text.getCharacterSize());
        text.setPosition(ref.text.getPosition());
        text.setColor(ref.text.getColor());

        font = ref.font;
        text.setFont(font);
    }

    ExceptionScene& operator=(const ExceptionScene& ref){

        Scene::operator=(ref);

        text.setString(ref.text.getString());
        text.setCharacterSize(ref.text.getCharacterSize());
        text.setPosition(ref.text.getPosition());
        text.setColor(ref.text.getColor());

        font = ref.font;
        text.setFont(font);

        return *this;
    }

private:

    void draw (sf::RenderTarget& target, sf::RenderStates) const override {

        target.draw(text);
    }

    sf::Text text;
    sf::Font font;
};


#endif //SFML_TEST_EXCEPTIONSCENE_HPP
