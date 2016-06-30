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

    //TODO redefinir ==
    void unregistrerObserver(Observer<T>& observer){
        //observers.remove(observer);
    }

protected:
    virtual void notifyObservers(T& type) =0;

protected:
    std::list<Observer<T>*> observers;
};


#endif //SFML_TEST_OBSERVABLE_HPP
