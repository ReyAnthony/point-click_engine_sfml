//
// Created by Anthony REY on 30/06/2016.
//

#ifndef SFML_TEST_OBSERVER_HPP
#define SFML_TEST_OBSERVER_HPP


#include <SFML/Graphics/RenderTarget.hpp>

template<class T>
class Observer {

public:
    virtual void notify(T& event, sf::RenderTarget& renderTarget) = 0;

};


#endif //SFML_TEST_OBSERVER_HPP
