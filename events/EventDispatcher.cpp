//
// Created by Anthony REY on 30/06/2016.
//

#include "EventDispatcher.hpp"

void EventDispatcher::notifyObservers(sf::Event& event, sf::RenderTarget& renderTarget) {

    for(auto& obs : Observable<sf::Event>::observers) {

        obs->notify(event, renderTarget);
    }
}