//
// Created by Anthony REY on 19/07/2016.
//

#ifndef SFML_TEST_LEVELSWITCHOBSERVER_HPP
#define SFML_TEST_LEVELSWITCHOBSERVER_HPP


#include "SwitchLevelAction.hpp"
#include "Observer.hpp"
#include "../game/GameScene.hpp"
#include "../game/Player.hpp"
#include "EventDispatcher.hpp"

class LevelSwitchObserver : public Observer<SwitchLevelAction> {

public:
    LevelSwitchObserver(std::map<std::string, GameScene*>& level_map, GameScene*& current_level, EventDispatcher& dispatcher);
    void notify(SwitchLevelAction& event, sf::RenderTarget& renderTarget);

private:
    std::map<std::string, GameScene*>& level_map;
    GameScene*& current_level;
    EventDispatcher& dispatcher;
};


#endif //SFML_TEST_LEVELSWITCHOBSERVER_HPP
