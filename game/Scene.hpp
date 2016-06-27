//
// Created by Anthony REY on 25/05/2016.
//

#ifndef SFML_TEST_SCENE_HPP
#define SFML_TEST_SCENE_HPP

#include <vector>
#include "Object.hpp"

class Scene : public sf::Drawable {

public:

    Scene();
    Scene(const Scene& ref);
    Scene & operator=(const Scene& ref);

    void setName(std::string level_name);
    void addBackground(std::string background_file);
    void addPlayer(Object& player);
    void addObject(Object& object);

    void update(sf::Time& deltaTime);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

    std::string level_name;
    std::vector<Object> objects;
    Object background;
    Object player;
};


#endif //SFML_TEST_SCENE_HPP
