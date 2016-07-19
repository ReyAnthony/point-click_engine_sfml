//
// Created by Anthony REY on 19/07/2016.
//

#include "LevelSwitchObserver.hpp"

void LevelSwitchObserver::notify(SwitchLevelAction& event, sf::RenderTarget& renderTarget) {

    std::cout << "got change level event to : " <<  event.getLevel() << std::endl;
    dispatcher.removeAllObservers();

    current_level = level_map[event.getLevel()];
    current_level->resetPlayerToDefaultPosition();
    dispatcher.registerObserver(*current_level);

}

LevelSwitchObserver::LevelSwitchObserver(std::map<std::string, GameScene*>& level_map, GameScene*& current_level, EventDispatcher& dispatcher)
        : level_map(level_map), current_level(current_level), dispatcher(dispatcher) {
}