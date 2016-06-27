//
// Created by Anthony REY on 25/05/2016.
//

#include "Scene.hpp"

Scene::Scene() {

}

Scene::Scene(const Scene& ref) {
    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    player = ref.player;
}

Scene &Scene::operator=(const Scene& ref) {

    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    player = ref.player;

    return *this;
}

void Scene::setName(std::string level_name) {
    this->level_name = level_name;
}

void Scene::addBackground(std::string background_file) {

    Object background(background_file, 0, 0, background_file);
    this->background = background;
}

void Scene::addPlayer(Object& player) {
    this->player = player;
}

void Scene::addObject(Object& object) {

    objects.push_back(object);
}

void Scene::update(sf::Time& deltaTime) {

    for(Object& obj : objects){
        obj.update(deltaTime);
    }
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(background);

    for(const sf::Drawable& obj : objects){
        target.draw(obj);
    }

    target.draw(player);
}