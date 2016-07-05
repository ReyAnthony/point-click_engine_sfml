//
// Created by Anthony REY on 27/06/2016.
//

#ifndef SFML_TEST_APPLICATION_HPP
#define SFML_TEST_APPLICATION_HPP

#include "translations/TranslationReader.hpp"
#include "translations/XMLTranslationReader.hpp"
#include "game/GameScene.hpp"
#include "conf/ConfReader.hpp"
#include "levels/LevelLoader.hpp"
#include "exceptions/ExceptionScene.hpp"
#include "events/EventDispatcher.hpp"
#include "game/Player.hpp"
#include "game/action_panel/ActionPanel.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <stack>

class Application {

public:
    ~Application();
    void start();

    static const int HEIGHT;
    static const int WIDTH;

private:

    void run();
    void initRenderer();
    void gameLoop();
    void cleanup();

    AbstractScene* current_scene;
    bool running = false;

    sf::RenderWindow* window;
    sf::View game_view;
    sf::View GUI_action_panel_view;
    sf::Clock clock;

    TxtConfReader conf;
    TranslationReader* trad;

    EventDispatcher eventDispatcher;

    Player* player_character;
    ActionPanel* action_panel;
};

TranslationReader *getTranslator(TxtConfReader& conf);

#endif //SFML_TEST_APPLICATION_HPP
