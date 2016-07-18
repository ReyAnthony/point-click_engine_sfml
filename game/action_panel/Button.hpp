//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_BUTTON_HPP
#define SFML_TEST_BUTTON_HPP


#include "../Object.hpp"
#include "../../exceptions/Exception.hpp"

class Button : public Object  {

public:

    Button(GUIActionsType actionType, std::string name, int x, int y, std::string sprite_file ) : Object(name, x, y, sprite_file),
                actionType(actionType) {}



    //TODO c'est sale revoir l'archi (genre object aurait une interface un actionable object pour les objets utilisables, hors bouttons)
    Action & doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType) override{

        throw Exception("doAction is not implemented for Buttons");
    }

    GUIActionsType doAction(sf::Event& event, sf::RenderTarget& renderTarget){

        if(isClicked(event, renderTarget)){
            return actionType;
        }

        return NOOP;

    }

    friend std::ostream& operator<< (std::ostream& stream, const Button& button){

        stream << button.getName() << std::endl;
        return stream;
    }

private:
    GUIActionsType actionType;
    bool isClicked(sf::Event& event, sf::RenderTarget& renderTarget) override {
        if(event.type == sf::Event::MouseButtonPressed){

            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            sf::Vector2f pixel_position(x, y);

            if (sprite.getGlobalBounds().contains(pixel_position)) {
                return true;
            }
        }
        return false;
    }

};


#endif //SFML_TEST_BUTTON_HPP
