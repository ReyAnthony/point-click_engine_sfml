//
// Created by Anthony REY on 25/05/2016.
//

#ifndef SFML_TEST_SCENE_HPP
#define SFML_TEST_SCENE_HPP

#include <vector>
#include "Object.hpp"

class Scene : public sf::Drawable {

public:

    Scene(){

    }

    Scene(const Scene& ref)
    {
        background = ref.background;

        objects = ref.objects;
        level_name = ref.level_name;
    }

    Scene& operator=(const Scene& ref){

        background = ref.background;

        objects = ref.objects;
        level_name = ref.level_name;
        return *this;
    }

    ~Scene()
    {

    }

    void setName(std::string level_name)
    {
        this->level_name = level_name;
    }

    void addBackground(std::string background_file){

        Object background(background_file, 0, 0, background_file);
        this->background = background;
    }

    void addObject(Object& object){

        objects.push_back(object);
    }

    void update(sf::Time& deltaTime){

        for(Object& obj : objects){
            obj.update(deltaTime);
        }
    }

private:

    virtual void draw (sf::RenderTarget& target, sf::RenderStates) const override {

        target.draw(background);

        for(const sf::Drawable& obj : objects){
            target.draw(obj);
        }
    }

    std::string level_name;
    std::vector<Object> objects;
    Object background;
};


#endif //SFML_TEST_SCENE_HPP
