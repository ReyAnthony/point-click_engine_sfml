//
// Created by Anthony REY on 26/06/2016.
//

#include "ExceptionScene.hpp"
#include "../Application.hpp"

ExceptionScene::ExceptionScene(std::string default_font_path, Exception& exception) {

    font.loadFromFile(default_font_path);

    text.setString("There was an issue with the configuration ! \n" + exception.getErrorMessage());
    text.setCharacterSize(20);
    text.setPosition(0,0);
    text.setColor(sf::Color::Red);
    text.setFont(font);
}

ExceptionScene::ExceptionScene(const ExceptionScene& ref)  {
    text.setString(ref.text.getString());
    text.setCharacterSize(ref.text.getCharacterSize());
    text.setPosition(ref.text.getPosition());
    text.setColor(ref.text.getColor());

    font = ref.font;
    text.setFont(font);
}

ExceptionScene &ExceptionScene::operator=(const ExceptionScene& ref) {

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

void ExceptionScene::update(sf::Time& deltaTime, sf::RenderWindow& window) {
    sf::View camera;
    camera.reset(sf::FloatRect(0,0, Application::WIDTH, Application::HEIGHT));
    camera.setCenter(Application::WIDTH / 2, Application::HEIGHT / 2);
    window.setView(camera);
}

void ExceptionScene::notify(sf::Event &event, sf::RenderTarget &renderTarget) {
    //no op
}