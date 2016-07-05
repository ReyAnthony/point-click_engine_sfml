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

    void update(sf::Time& deltaTime);
    void setPosX(int pos_x);
    void setPosY(int pos_y);
    int getPosX() const;
    int getPosY() const;
    int getYLimit() const;
    int getHeight() const;
    int getWidth() const;
    std::string getName() const;

    virtual AbstractAction doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType);

protected:

    bool isClicked(sf::Event& event, sf::RenderTarget& renderTarget){

        if(event.type == sf::Event::MouseButtonPressed){

            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            sf::Vector2i absolute_position(x, y);
            auto relative_position = renderTarget.mapPixelToCoords(absolute_position);

            if (sprite.getGlobalBounds().contains(relative_position)) {
                return true;
            }
        }
        return false;
    }


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
};


#endif //SFML_TEST_OBJECT_HPP
