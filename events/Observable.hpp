//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_OBSERVABLE_HPP
#define SFML_TEST_OBSERVABLE_HPP


#include <list>
#include "Observer.hpp"

template <class T>
class Observable {

public:
    void registerObserver(Observer<T>& observer){
        observers.push_back(&observer);
    }

    void removeAllObservers(){
        observers.clear();
    }

protected:
    virtual void notifyObservers(T& type,  sf::RenderTarget&renderTarget) =0;

protected:
    std::list<Observer<T>*> observers;
};


#endif //SFML_TEST_OBSERVABLE_HPP
