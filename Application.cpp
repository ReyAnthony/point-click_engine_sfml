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

    if(speech_panel != nullptr)
        delete speech_panel;

    if(action_panel != nullptr)
        delete action_panel;


}

void Application::start() {
    try {

        conf.loadConfiguration();
        trad = getTranslator(conf);

        //std::cout << trad->getTranslationFromKey("level_1_name") << std::endl;

        player_character = new Player(conf.getPlayerName(),
                                      0,
                                      0,
                                      conf.getPlayerSpritePath(),
                                      conf.getPlayerFrames(),
                                      conf.getPlayerMsBeetwenEachFrames());

        try{

            speech_panel = new SpeechPanel(conf.getDefaultFontPath());
            action_panel = new ActionPanel(conf);
            LevelLoader level_loader(*trad,
                                     conf,
                                     *player_character,
                                     event_dispatcher,
                                     *action_panel,
                                     *speech_panel);

            auto starting_level_file = conf.getStartingLevel();
            this->current_scene = level_loader.generateGameSceneFromLevelFile(starting_level_file);
            event_dispatcher.registerObserver(*current_scene);
        }
        catch(boost::exception &e){
            throw Exception(boost::diagnostic_information(e));
        }
    }
    catch(Exception &e ) {

        has_exception = true;
        this->current_scene = new ExceptionScene(conf.getDefaultFontPath(), e);
    }

    try {
        running = true;
        run();
    }
    catch(Exception &e){

        delete current_scene;
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
                                                conf.getAppName() /*, sf::Style::Fullscreen */);
    window->setFramerateLimit(conf.getFramerate());

    GUI_panel_view.reset(sf::FloatRect(0, 0, Application::WIDTH, 53));
    GUI_panel_view.setViewport(sf::FloatRect(0, 0, 1, 0.08));
}

void Application::gameLoop() {
    clock.restart();

    while(running) {

        sf::Time time_for_frame = clock.restart();
        sf::Event event;

        sf::View game_view = window->getDefaultView();
        game_view.setCenter(player_character->getPosX(), Application::HEIGHT / 2);
        window->setView(game_view);

        while (window->pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed){

                event_dispatcher.notifyObservers(event, *window);
            }

            if (event.type == sf::Event::Closed)
            {
                window->close();
                running = false;
                break;
            }
        }

        window->clear(sf::Color::Black);
        current_scene->update(time_for_frame, *window);
        window->draw(*current_scene);

       if(!has_exception){
            window->setView(GUI_panel_view);
            window->draw(*action_panel);
            window->draw(*speech_panel);
       }

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
        return new JSONTranslationReader(conf.getDefaultTranslationFile());
    else
        throw Exception("No such configuration type "+ conf.getDefaultConfType());
}
