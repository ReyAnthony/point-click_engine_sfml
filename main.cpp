#include "translations/TranslationReader.hpp"
#include "translations/XMLTranslationReader.hpp"
#include "game/Scene.hpp"
#include "conf/ConfReader.hpp"
#include "levels/LevelLoader.hpp"
#include "exceptions/ExceptionScene.hpp"

#include <stack>

namespace PCGE
{

    class App
    {
    public:

        App()
        {
            start();
        }

        ~App()
        {
            delete window;
            delete trad;
            delete current_scene;
        }

        void start()
        {
            try {

                conf.loadConfiguration();
                auto map = conf.getConfigurationValues();

                //should make a generator ?
                if (map[conf.DEFAULT_CONF_TYPE] == "conf_xml")
                    trad = new XMLTranslationReader(conf.getDefaultTranslationFile());
                //else if(map[conf.DEFAULT_CONF_TYPE] == "conf_json")
                //    trad = new JSONTranslationReader(conf.getDefaultTranslationFile());
                else
                    throw new Exception("No such configuration type "+ map[conf.DEFAULT_CONF_TYPE]);

                auto starting_level = conf.getStartingLevel();
                LevelLoader level_loader(*trad, conf);
                this->current_scene = level_loader.generateDataFromLevelFile(starting_level);


            }
            catch(Exception &e )
            {
                ExceptionScene* ex = new ExceptionScene(conf.getDefaultFont(), e);
                this->current_scene = ex;
            }

            try {
                running = true;
                run();
            }
            catch(Exception &e){

                delete current_scene;
                ExceptionScene* ex = new ExceptionScene(conf.getDefaultFont(), e);
                this->current_scene = ex;

            }
        }

    private:

        void run()
        {
            initRenderer();
            gameLoop();
            cleanup();
        }

        void initRenderer()
        {
            window = new sf::RenderWindow(sf::VideoMode(1280, 720), conf.getAppName());
        }

        void gameLoop()
        {
            clock.restart();

            while(running) {

                sf::Time time_for_frame = clock.restart();
                sf::Event event;

                while (window->pollEvent(event))
                {

                    if (event.type == sf::Event::Closed)
                    {
                        window->close();
                        running = false;
                    }
                }

                window->clear(sf::Color::Black);
                current_scene->update(time_for_frame);
                window->draw(*current_scene);
                window->display();
            }
        }

        void cleanup()
        {
            //utilisé pour des clean qui ne touchent pas la mémoire ?
        }

        Scene* current_scene;
        bool running = false;

        sf::RenderWindow* window;
        sf::Clock clock;

        TxtConfReader conf;
        TranslationReader* trad;
    };
}

using namespace PCGE;
using namespace std;

int main(int argc, char** argv) {

    App app;
    return 0;
}