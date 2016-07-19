//
// Created by Anthony REY on 25/05/2016.
//

#ifndef SFML_TEST_SCENE_HPP
#define SFML_TEST_SCENE_HPP

#include <vector>
#include <list>
#include "Object.hpp"
#include "AbstractScene.hpp"
#include "action_panel/ActionPanel.hpp"
#include "speech_panel/SpeechPanel.hpp"
#include "../events/Observable.hpp"
#include "../events/SwitchLevelAction.hpp"

class GameScene : public AbstractScene , public Observable<SwitchLevelAction>{

public:

    GameScene(Object& player, ActionPanel& actionPanel, SpeechPanel& speech_panel);
    GameScene(const GameScene & ref);
    GameScene & operator=(const GameScene & ref);

    void setName(std::string level_name);
    void setBackground(std::string background_file);
    void setDefaultPos(int x, int y);
    void resetPlayerToDefaultPosition();
    void addObject(Object& object);
    Object & getLastInsertedObject();

    void virtual update(sf::Time& deltaTime,  sf::RenderWindow& window) override;
    virtual void notify(sf::Event &event, sf::RenderTarget &renderTarget) override;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    void notifyObservers(SwitchLevelAction& type, sf::RenderTarget&renderTarget) override;
    void updateDrawingPriorities();

    std::string level_name;
    std::vector<Object*> objects;
    std::vector<const Object*> drawing_list;

    int default_x;
    int default_y;

    Object background;
    Object& player;
    ActionPanel& action_panel;
    SpeechPanel& speech_panel;
    Object* last_inserted;
    GUIActionsType current_action = NOOP;
};



#endif //SFML_TEST_SCENE_HPP
