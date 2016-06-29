//
// Created by Anthony REY on 27/06/2016.
//

#include "Application.hpp"

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
        show_fps = conf.shouldShowFps();

        player_character = new Object(conf.getPlayerName(),
                                      0,
                                      0,
                                      conf.getPlayerSpritePath(),
                                      conf.getPlayerFrames(),
                                      conf.getPlayerMsBeetwenEachFrames(),
                                      0 /*ignored for the player*/);

        //Creer une classe qui renvoie le translateur a utiliser
        if (conf.getDefaultConfType() == "conf_xml")
            trad = new XMLTranslationReader(conf.getDefaultTranslationFile());
        else if(conf.getDefaultConfType() ==  "conf_json")
            throw Exception("Not implemented yet : conf_json");
        else
            throw Exception("No such configuration type "+ conf.getDefaultConfType());

        auto starting_level_file = conf.getStartingLevel();
        LevelLoader level_loader(*trad, conf, *player_character);

        try{
            this->current_scene = level_loader.generateDataFromLevelFile(starting_level_file);
        }
        catch(boost::exception &e){
            throw Exception(boost::diagnostic_information(e));
        }

    }
    catch(Exception &e )
    {
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

    window = new sf::RenderWindow(sf::VideoMode(Application::WIDTH, Application::HEIGHT), conf.getAppName());
    window->setFramerateLimit(conf.getFramerate());
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, Application::WIDTH, Application::HEIGHT));

    //replace by a FPS displayer class ?
    if(show_fps){
        font.loadFromFile(conf.getDefaultFont());
        text.setFont(font);
        text.setCharacterSize(20);
        text.setColor(sf::Color::White);
        text.setPosition(0,0);
    }
}

void Application::gameLoop() {
    clock.restart();

    while(running) {

        sf::Time time_for_frame = clock.restart();
        float framerate = 1 / time_for_frame.asSeconds();

        sf::Event event;

        while (window->pollEvent(event))
        {

            //TODO FOR TESTING PURPOSE
            //FOR TESTING PURPOSE
            auto current_pos_x = current_scene->getPlayer().getPosX();
            auto current_pos_y = current_scene->getPlayer().getPosY();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                current_scene->getPlayer().setPosX(current_pos_x - 10);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                current_scene->getPlayer().setPosX(current_pos_x + 10);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                current_scene->getPlayer().setPosY(current_pos_y - 10);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                current_scene->getPlayer().setPosY(current_pos_y + 10);
            //FOR TESTING PURPOSE
            //FOR TESTING PURPOSE

            if (event.type == sf::Event::Closed)
            {
                window->close();
                running = false;
            }
        }

        window->clear(sf::Color::Black);
        current_scene->update(time_for_frame, *window);
        window->draw(*current_scene);

        if(show_fps){
            std::stringstream ss;
            ss << framerate;
            text.setString(ss.str() + " FPS");
            window->draw(text);
        }

        window->display();
    }
}

void Application::cleanup() {
    //utilisé pour des clean qui ne touchent pas la mémoire ?
}

const int Application::HEIGHT = 720;
const int Application::WIDTH = 1280;