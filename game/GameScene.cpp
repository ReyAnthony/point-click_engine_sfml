//
// Created by Anthony REY on 25/05/2016.
//

#include "GameScene.hpp"
#include "../Application.hpp"



GameScene::GameScene(Object& player, ActionPanel& actionPanel, SpeechPanel& speech_panel) :
        player(player),
        action_panel(actionPanel),
        speech_panel(speech_panel){
}

GameScene::GameScene(const GameScene & ref) : player(ref.player),  action_panel(ref.action_panel), speech_panel(ref.speech_panel){
    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    last_inserted = ref.last_inserted;
}

GameScene &GameScene::operator=(const GameScene & ref) {

    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    player = ref.player;
    action_panel = ref.action_panel;
    speech_panel = ref.speech_panel;
    last_inserted = ref.last_inserted;

    return *this;
}

void GameScene::setName(std::string level_name) {
    this->level_name = level_name;
}

void GameScene::setBackground(std::string background_file) {

    Object background(background_file, 0, 0, background_file);
    this->background = background;
}

void GameScene::addObject(Object& object) {

    objects.push_back(&object);

    //we sort the objects so that they are in their priority order
    std::sort(objects.begin(), objects.end(),
              [this](Object* a, Object* b) {
                  auto tested = (a->getPosY() + a->getYLimit());
                  auto other = (b->getPosY() + b->getYLimit());

                  return tested < other;
              });

    last_inserted = &object;
}

void GameScene::update(sf::Time& deltaTime, sf::RenderWindow& window) {

    bool player_had_a_colisions = false;
    drawing_list.clear();

    for(Object* obj : objects){
        obj->update(deltaTime);

        if(player.isCollidingUsingColliders(*obj))
            player_had_a_colisions = true;
    }

    player.update(deltaTime);

    if(player_had_a_colisions || player.getPosX() <= 1
       || player.getPosY() <= 1
       || player.getPosX() > background.getWidth()
       || player.getPosY() > background.getHeight())
    {
        ((Player&)player).revertToPositionBeforeUpdate();
    }

    updateDrawingPriorities();
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(background);

    for(const sf::Drawable* obj : drawing_list){
        target.draw(*obj);
    }
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
    return *last_inserted;
}

void GameScene::notify(sf::Event &event, sf::RenderTarget &renderTarget) {

    if(speech_panel.isVisible()){

        speech_panel.goToNextSentence();
    }
    else
    {
        current_action = action_panel.doAction(event, renderTarget);

        //backward because we treat those in front first
        for(auto it = objects.rbegin(); it != objects.rend(); ++it ){

            Action & action = (*it)->doAction(event, renderTarget, current_action);
            auto actionType = action.getActionType();

            if(actionType == TALK || actionType == SEE){

                auto sentences = action.getSentences();
                speech_panel.setSentences(sentences);

            }
            else if( actionType == GRAB ){

                if(player.isColliding(**it)){
                    std::cout << "GRAB" << " " <<  (*it)->getName() << std::endl;
                }
                else{
                    std::vector<std::string> sentences;
                    sentences.push_back("I'm too far away ... //FIXME");
                    speech_panel.setSentences(sentences);
                }
            }
            else if (actionType == USE){

                if(player.isColliding(**it)){
                    std::cout << "USE" << " " <<  (*it)->getName() << std::endl;
                    SwitchLevelAction switchLevelAction(action.getNewLevel());
                    this->notifyObservers(switchLevelAction, renderTarget);
                    break;
                }
                else{
                    std::vector<std::string> sentences;
                    sentences.push_back("I'm too far away ... //FIXME");
                    speech_panel.setSentences(sentences);
                }

            }
            else if( actionType == GOTO){
                std::cout << "GOTO" << " " <<  (*it)->getName() << std::endl;
                //pathfind ...
            }

            if(actionType != NOOP)
                break;
        }

        //player.doAction(event, renderTarget, current_action);

    }

}