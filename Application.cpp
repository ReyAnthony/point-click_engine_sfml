//
// Created by Anthony REY on 27/06/2016.
//

#include "Application.hpp"
#include "events/EventDispatcher.hpp"
#include "game/Player.hpp"

Application::~Application() {
    delete window;
    delete trad;

    if(player_character != nullptr)
        delete player_character;

    if(current_scene != nullptr)
        delete current_scene;
}

void Application::start() {
    try {

        conf.loadConfiguration();

        player_character = new Player(conf.getPlayerName(),
                                      0,
                                      0,
                                      conf.getPlayerSpritePath(),
                                      conf.getPlayerFrames(),
                                      conf.getPlayerMsBeetwenEachFrames(),
                                      0 /*ignored for the player*/);

        eventDispatcher.registerObserver(*player_character);

        trad = getTranslator(conf);
        auto starting_level_file = conf.getStartingLevel();
        LevelLoader level_loader(*trad, conf, *player_character, eventDispatcher);

        try{
            this->current_scene = level_loader.generateDataFromLevelFile(starting_level_file);
        }
        catch(boost::exception &e){
            throw Exception(boost::diagnostic_information(e));
        }
    }
    catch(Exception &e ) {
        this->current_scene =  new ExceptionScene(conf.getDefaultFont(), e);
    }

    try {
        running = true;
        run();
    }
    catch(Exception &e){

        delete current_scene;
        this->current_scene = new ExceptionScene(conf.getDefaultFont(), e);
    }
}

void Application::run() {
    initRenderer();
    gameLoop();
    cleanup();
}

void Application::initRenderer() {

    window = new sf::RenderWindow(sf::VideoMode((unsigned int) Application::WIDTH,
                                                (unsigned int) Application::HEIGHT),
                                                conf.getAppName());
    window->setFramerateLimit(conf.getFramerate());
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, Application::WIDTH, Application::HEIGHT));
}

void Application::gameLoop() {
    clock.restart();

    while(running) {

        sf::Time time_for_frame = clock.restart();
        sf::Event event;

        while (window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
                eventDispatcher.notifyObservers(event);

            if (event.type == sf::Event::Closed)
            {
                window->close();
                running = false;
            }
        }

        window->clear(sf::Color::Black);
        current_scene->update(time_for_frame, *window);
        window->draw(*current_scene);
        window->display();
    }
}

void Application::cleanup() {
    //utilisé pour des clean qui ne touchent pas la mémoire ?
}

const int Application::HEIGHT = 720;
const int Application::WIDTH = 1280;

TranslationReader *getTranslator(TxtConfReader& conf) {

    auto conf_type = conf.getDefaultConfType();

    if (conf_type == "conf_xml")
        return new XMLTranslationReader(conf.getDefaultTranslationFile());
    else if(conf_type == "conf_json")
        throw Exception("Not implemented yet : conf_json");
    else
        throw Exception("No such configuration type "+ conf.getDefaultConfType());
}
