//
// Created by Anthony REY on 25/06/2016.
//

#ifndef SFML_TEST_OBJECT_HPP
#define SFML_TEST_OBJECT_HPP


#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "../events/GUIActionType.hpp"
#include "AbstractAction.hpp"

class Object : public sf::Drawable {

public:

    Object();
    Object(std::string name, int pos_x, int pos_y, std::string texture_file, int frames = 1, int ms_beetwen_frames = 0, int y_limit = -5000);
    Object & operator=(const Object& ref);
    Object(const Object& ref);
    ~Object(){
        for(auto action : actions){
            delete action.second;
        }
    }

    void update(sf::Time& deltaTime);
    void setPosX(int pos_x);
    void setPosY(int pos_y);
    int getPosX() const;
    int getPosY() const;
    int getYLimit() const;
    int getHeight() const;
    int getWidth() const;
    std::string getName() const;
    void addAction(GUIActionsType key, AbstractAction* action);

    virtual AbstractAction& doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType);

protected:

    bool isClicked(sf::Event& event, sf::RenderTarget& renderTarget);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
    void initTextureAndSprite(std::string texture_file);

    std::string name;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Time elapsed_time;
    int ms_beetwen_frames = 0;
    int frames = 1;
    int current_frame = 0;
    int y_limit = -5000;

    bool animated = false;

    std::map<GUIActionsType, AbstractAction*> actions;
};


#endif //SFML_TEST_OBJECT_HPP
