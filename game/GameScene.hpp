//
// Created by Anthony REY on 25/05/2016.
//

#ifndef SFML_TEST_SCENE_HPP
#define SFML_TEST_SCENE_HPP

#include <vector>
#include <list>
#include "Object.hpp"
#include "AbstractScene.hpp"

class GameScene : public AbstractScene {

public:

    GameScene(Object& player);
    GameScene(const GameScene & ref);
    GameScene & operator=(const GameScene & ref);

    void setName(std::string level_name);
    void addBackground(std::string background_file);
    void addPlayer(Object& player);
    void addObject(Object& object);
    Object & getLastInsertedObject();

    Object& getPlayer();

    void virtual update(sf::Time& deltaTime,  sf::RenderWindow& window);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
    void updateDrawingPriorities();

    std::string level_name;
    std::vector<Object> objects;
    std::vector<Object*> drawing_list;

    Object background;
    Object& player;
};



#endif //SFML_TEST_SCENE_HPP
