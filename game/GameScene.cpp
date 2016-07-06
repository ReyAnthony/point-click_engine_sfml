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
}

GameScene &GameScene::operator=(const GameScene & ref) {

    background = ref.background;

    objects = ref.objects;
    level_name = ref.level_name;
    player = ref.player;
    action_panel = ref.action_panel;
    speech_panel = ref.speech_panel;

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
}

void GameScene::update(sf::Time& deltaTime, sf::RenderWindow& window) {

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
    return **(objects.end() - 1);
}

void GameScene::notify(sf::Event &event, sf::RenderTarget &renderTarget) {

    if(!speech_panel.isVisible())
    {
        current_action = action_panel.doAction(event, renderTarget);

        //backward because we treat those in front first
        for(auto it = objects.rbegin(); it != objects.rend(); ++it ){

            AbstractAction& action = (*it)->doAction(event, renderTarget, current_action);
            auto actionType = action.getActionType();

            if(actionType == TALK && action.getActionType() == TALK){

                TalkAction& talk = (TalkAction&) action;
                auto sentences = talk.getSentences();
                speech_panel.setSentences(sentences);
            }
            else if (actionType == SEE && action.getActionType() == SEE){

                SeeAction& see = (SeeAction&) action;
                auto sentences = see.getSentences();
                speech_panel.setSentences(sentences);

            }
            else if( actionType == GRAB ){
                std::cout << "GRAB" << " " <<  (*it)->getName() << std::endl;
            }
            else if (actionType == USE){
                std::cout << "USE" << " " <<  (*it)->getName() << std::endl;
            }
            else if( actionType == GOTO){
                std::cout << "GOTO" << " " <<  (*it)->getName() << std::endl;
            }

            if(actionType != NOOP)
                break;
        }

        player.doAction(event, renderTarget, current_action);

    }
    else{

        speech_panel.goToNextSentence();

    }

}