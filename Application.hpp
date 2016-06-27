//
// Created by Anthony REY on 27/06/2016.
//

#ifndef SFML_TEST_APPLICATION_HPP
#define SFML_TEST_APPLICATION_HPP

#include "translations/TranslationReader.hpp"
#include "translations/XMLTranslationReader.hpp"
#include "game/Scene.hpp"
#include "conf/ConfReader.hpp"
#include "levels/LevelLoader.hpp"
#include "exceptions/ExceptionScene.hpp"

#include <stack>

class Application {

public:
    ~Application();
    void start();

private:

    void run();
    void initRenderer();
    void gameLoop();
    void cleanup();

    Scene* current_scene;
    bool running = false;
    bool show_fps = false;

    sf::RenderWindow* window;
    sf::Clock clock;

    TxtConfReader conf;
    TranslationReader* trad;

    Object* player_character;

    //FPS
    sf::Text text;
    sf::Font font;
};


#endif //SFML_TEST_APPLICATION_HPP
