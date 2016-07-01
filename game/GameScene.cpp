//
// Created by Anthony REY on 25/05/2016.
//

#include "GameScene.hpp"
#include "../Application.hpp"

GameScene::GameScene(Object& player) : player(player){

}

GameScene::GameScene(const GameScene & ref) : player(ref.player){
    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;

    //no need to copy the drawing list
}

GameScene &GameScene::operator=(const GameScene & ref) {

    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    player = ref.player;

    return *this;
}

void GameScene::setName(std::string level_name) {
    this->level_name = level_name;
}

void GameScene::addBackground(std::string background_file) {

    Object background(background_file, 0, 0, background_file);
    this->background = background;
}

void GameScene::addPlayer(Object& player) {
    this->player = player;
}

void GameScene::addObject(Object& object) {

    objects.push_back(&object);

    //we sort the objects so that they in their priority order
    std::sort(objects.begin(), objects.end(),
              [this](Object* a, Object* b) {
                  auto tested = (a->getPosY() + a->getYLimit());
                  auto other = (b->getPosY() + b->getYLimit());

                  return tested < other;
              });
}

void GameScene::update(sf::Time& deltaTime, sf::RenderWindow& window) {

    sf::View camera;
    camera.reset(sf::FloatRect(0,0, Application::WIDTH, Application::HEIGHT));
    camera.setCenter(player.getPosX(), Application::HEIGHT / 2);
    window.setView(camera);

    drawing_list.clear();

    for(Object* obj : objects){
        obj->update(deltaTime);
    }

    updateDrawingPriorities();
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(background);

    for(const sf::Drawable* obj : drawing_list){
        target.draw(*obj);
    }
}

Object &GameScene::getPlayer() {
    return player;
}

void GameScene::updateDrawingPriorities() {

    int index_insert_player = 0;
    int current_index = 0;

    for(auto it = objects.begin(); it != objects.end(); ++it, ++current_index)
    {
        auto player_pos = (player.getPosY()+ player.getHeight());
        auto other = ((*it)->getPosY() + (*it)->getYLimit());

        drawing_list.push_back(*it);
        if(player_pos > other){
            index_insert_player = current_index + 1;
        }
    }

    auto iter = drawing_list.begin();
    drawing_list.insert(iter + index_insert_player, &player);
}

Object &GameScene::getLastInsertedObject() {
    return **objects.end();
}

void GameScene::notify(sf::Event &event, sf::RenderTarget &renderTarget) {
    //backward because we treat those in front first
    for(auto it = objects.rbegin(); it != objects.rend(); ++it ){
        Action action = (*it)->doAction(event, renderTarget);

        //Put the action in an action list, then execute it on next update ?
        //We should not put 2 actions in the list
        auto actionType = action.getActionType();
        if(actionType == Action::NOOP){
            std::cout << "NOOP" << " " <<  (*it)->getName() << std::endl;
        }
        else if(actionType == Action::TALK){
            //if that's not a NOOP, we don't even bother forwarding events to other entities
            std::cout << "TALK" << " " <<  (*it)->getName() << std::endl;
            break;
        }
    }

    player.doAction(event, renderTarget);
}