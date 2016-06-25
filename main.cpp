#include "translations/TranslationReader.hpp"
#include "translations/XMLTranslationReader.hpp"
#include "game/Scene.hpp"
#include "conf/ConfReader.hpp"
#include "exceptions/NoSuchConfType.hpp"
#include "levels/LevelLoader.hpp"

#include <SFML/Graphics.hpp>
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
        }

        void start()
        {
            try {

                conf.loadConfiguration();
                auto map = conf.getConfigurationValues();

                //should make a generator ?
                if (map[conf.DEFAULT_CONF_TYPE] == "conf_xml")
                    trad = new XMLTranslationReader(conf.getDefaultTranslationFile());
                else
                    throw new NoSuchConfType();

                auto starting_level = conf.getStartingLevel();
                LevelLoader level_loader(*trad, conf);
                auto generated_scene = level_loader.generateDataFromLevelFile(starting_level);

                running = true;
                run();
            }
            catch(KeyException &e )
            {
                std::cout << "Key exception" << std::endl;
            }
            catch(NoSuchConfType &e)
            {
                std::cout << "No such conf Type" << std::endl;
                //apeller une fonction qui affiche le message d'erreur
                //puis clean lorsqu'on appuie une touche
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
            window = new sf::RenderWindow(sf::VideoMode(800, 600), app_title);
        }

        void gameLoop()
        {
            while(running) {

                sf::Event event;

                while (window->pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window->close();
                        running = false;
                    }
                }

                window->clear();
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
        std::string app_title;

        TxtConfReader conf;
        TranslationReader *trad;
    };
}

using namespace PCGE;
using namespace std;

int main(int argc, char** argv) {

    App app;
    return 0;
}