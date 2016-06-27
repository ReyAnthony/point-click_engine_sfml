//
// Created by Anthony REY on 25/05/2016.
//

#include "Scene.hpp"
#include "../Application.hpp"

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

    //we sort the objects so that they in their priority order
    std::sort(objects.begin(), objects.end(),
              [this](Object& a, Object& b) {
                  auto tested = (a.getPosY() + a.getYLimit());
                  auto other = (b.getPosY() + b.getYLimit());

                  return tested < other;
              });
}

void Scene::update(sf::Time& deltaTime, sf::RenderWindow& window) {

    sf::View camera;
    camera.reset(sf::FloatRect(0,0, Application::WIDTH, Application::HEIGHT));
    camera.setCenter(player.getPosX(), Application::HEIGHT / 2);
    window.setView(camera);

    drawing_list.clear();

    for(Object& obj : objects){
        obj.update(deltaTime);
    }

    updateDrawingPriorities();
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(background);

    for(const sf::Drawable* obj : drawing_list){
        target.draw(*obj);
    }
}

Object &Scene::getPlayer() {
    return player;
}

void Scene::updateDrawingPriorities() {

    int index_insert_player = 0;
    int current_index = 0;

    for(auto it = objects.begin(); it != objects.end(); ++it, ++current_index)
    {
        auto player_pos = (player.getPosY()+ player.getHeight());
        auto other = (it->getPosY() + it->getYLimit());

        drawing_list.push_back(&(*it));
        if(player_pos > other){
            index_insert_player = current_index + 1;
        }
    }

    auto iter = drawing_list.begin();
    drawing_list.insert(iter + index_insert_player, &player);
}