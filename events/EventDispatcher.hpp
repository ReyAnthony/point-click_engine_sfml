//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_EVENTDISPATCHER_HPP
#define SFML_TEST_EVENTDISPATCHER_HPP

#include <SFML/Window/Event.hpp>
#include "Observable.hpp"

class EventDispatcher : public Observable<sf::Event> {

public:
    virtual void notifyObservers(sf::Event& event, sf::RenderTarget& renderTarget) override {

        for(auto& obs : Observable<sf::Event>::observers) {

            obs->notify(event, renderTarget);
        }
    }

};


#endif //SFML_TEST_EVENTDISPATCHER_HPP
