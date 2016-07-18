//
// Created by Anthony REY on 27/06/2016.
//

#ifndef SFML_TEST_APPLICATION_HPP
#define SFML_TEST_APPLICATION_HPP

#include "translations/TranslationReader.hpp"
#include "translations/JSONTranslationReader.hpp"
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
    sf::View GUI_panel_view;
    sf::Clock clock;

    TxtConfReader conf;
    TranslationReader* trad;

    EventDispatcher event_dispatcher;

    Player* player_character;
    ActionPanel* action_panel;
    SpeechPanel* speech_panel;
    XMLActionDefaultReader* xml_action_default_reader;

    bool has_exception;
};

TranslationReader *getTranslator(TxtConfReader& conf);

#endif //SFML_TEST_APPLICATION_HPP
