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

    Object();
    Object(std::string name, int pos_x, int pos_y, std::string texture_file, int frames, int ms_beetwen_frames);
    Object(std::string name, int pos_x, int pos_y, std::string texture_file);
    Object & operator=(const Object& ref);
    Object(const Object& ref);

    void update(sf::Time& deltaTime);
    void setPosX(int pos_x);
    void setPosY(int pos_y);

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

    bool animated = false;
};


#endif //SFML_TEST_OBJECT_HPP
