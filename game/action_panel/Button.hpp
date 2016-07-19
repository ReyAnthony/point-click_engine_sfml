//
// Created by Anthony REY on 03/07/2016.
//

#ifndef SFML_TEST_BUTTON_HPP
#define SFML_TEST_BUTTON_HPP


#include "../Object.hpp"
#include "../../exceptions/Exception.hpp"

class Button : public Object  {

public:

    Button(GUIActionsType actionType, std::string name, int x, int y, std::string sprite_file );
    Action & doAction(sf::Event& event, sf::RenderTarget& renderTarget, GUIActionsType actionType);
    GUIActionsType doAction(sf::Event& event, sf::RenderTarget& renderTarget);

    std::ostream friend &operator<<(std::ostream& stream, const Button& button) {

        stream << button.getName() << std::endl;
        return stream;
    }

private:
    GUIActionsType actionType;
    bool isClicked(sf::Event& event, sf::RenderTarget& renderTarget);

};


#endif //SFML_TEST_BUTTON_HPP
