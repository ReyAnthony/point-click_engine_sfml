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
#include "Action.hpp"

class Object : public sf::Drawable {

public:

    Object();
    Object(std::string name, int pos_x, int pos_y, std::string texture_file, int frames = 1, int ms_beetwen_frames = 0, int y_limit = -5000);
    Object & operator=(const Object& ref);
    Object(const Object& ref);
    ~Object();

    virtual void update(sf::Time& deltaTime);
    void setPosX(int pos_x);
    void setPosY(int pos_y);
    int getPosX() const;
    int getPosY() const;
    int getYLimit() const;
    int getHeight() const;
    int getWidth() const;
    std::string getName() const;
    void setActions(std::map<GUIActionsType, Action *> actions);
    void addAction(GUIActionsType key, Action * action);

    virtual Action & doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType);

    bool isColliding(Object& other);

protected:

    virtual bool isClicked(sf::Event& event, sf::RenderTarget& renderTarget);
    sf::Sprite sprite;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
    void initTextureAndSprite(std::string texture_file);

    std::string name;
    sf::Texture texture;

    sf::Time elapsed_time;
    int ms_beetwen_frames = 0;
    int frames = 1;
    int current_frame = 0;
    int y_limit = -5000;

    bool animated = false;

    std::map<GUIActionsType, Action*> actions;
};


#endif //SFML_TEST_OBJECT_HPP
