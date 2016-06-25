//
// Created by Anthony REY on 25/06/2016.
//

#ifndef SFML_TEST_OBJECT_HPP
#define SFML_TEST_OBJECT_HPP


#include <iosfwd>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Object : public sf::Drawable {

public:

    Object()
    {

    }

    Object(std::string name, int pos_x, int pos_y, std::string texture_file){

        this->name = name;
        this->pos_x = pos_x;
        this->pos_y = pos_y;

        if(this->texture.loadFromFile(texture_file))
        {
            this->sprite.setTexture(texture);
            this->sprite.setPosition(pos_x, pos_y);
        }
        else
            std::cerr << "failed to load the texture" << std::endl;
    }

    Object& operator = (const Object& ref){

        name = ref.name;
        pos_x = ref.pos_x;
        pos_y = ref.pos_y;

        texture = ref.texture;
        sprite = ref.sprite;
        sprite.setTexture(texture);

        return *this;
    }

    Object(const Object& ref)
    {
        name = ref.name;
        pos_x = ref.pos_x;
        pos_y = ref.pos_y;

        texture = ref.texture;
        sprite = ref.sprite;
        sprite.setTexture(texture);

    }

protected:
    virtual void draw (sf::RenderTarget& target, sf::RenderStates) const override {

        target.draw(sprite);
    }


private:
    std::string name;
    int pos_x = 0;
    int pos_y = 0;
    sf::Texture texture;
    sf::Sprite sprite;

};


#endif //SFML_TEST_OBJECT_HPP
