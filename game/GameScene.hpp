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

    void virtual update(sf::Time& deltaTime,  sf::RenderWindow& window) override;

    virtual void notify(sf::Event &event, sf::RenderTarget &renderTarget) override {
        //backward because we treat those in front first
        for(auto it = objects.rbegin(); it != objects.rend(); ++it ){
            (*it)->notify(event, renderTarget);
        }
    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    void updateDrawingPriorities();

    std::string level_name;
    std::vector<Object*> objects;
    std::vector<const Object*> drawing_list;

    Object background;
    Object& player;
};



#endif //SFML_TEST_SCENE_HPP
