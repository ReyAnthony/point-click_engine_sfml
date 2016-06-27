//
// Created by Anthony REY on 26/06/2016.
//

#include "ExceptionScene.hpp"

ExceptionScene::ExceptionScene(std::string default_font_path, Exception& exception) : Scene() {

    font.loadFromFile(default_font_path);

    text.setString("There was an issue with the configuration ! \n" + exception.getErrorMessage());
    text.setCharacterSize(20);
    text.setPosition(0,0);
    text.setColor(sf::Color::Red);
    text.setFont(font);
}

ExceptionScene::ExceptionScene(const ExceptionScene& ref) : Scene(ref) {
    text.setString(ref.text.getString());
    text.setCharacterSize(ref.text.getCharacterSize());
    text.setPosition(ref.text.getPosition());
    text.setColor(ref.text.getColor());

    font = ref.font;
    text.setFont(font);
}

ExceptionScene &ExceptionScene::operator=(const ExceptionScene& ref) {

    Scene::operator=(ref);

    text.setString(ref.text.getString());
    text.setCharacterSize(ref.text.getCharacterSize());
    text.setPosition(ref.text.getPosition());
    text.setColor(ref.text.getColor());

    font = ref.font;
    text.setFont(font);

    return *this;
}

void ExceptionScene::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(text);
}