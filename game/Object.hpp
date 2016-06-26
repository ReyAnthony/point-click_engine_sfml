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

    Object(){

    }

    Object(std::string name, int pos_x, int pos_y, std::string texture_file, int frames, int ms_beetwen_frames)
    {

        //TODO throw exception if frame / ms / pos / wrong  etc...

        this->name = name;
        this->pos_x = pos_x;
        this->pos_y = pos_y;

        this->ms_beetwen_frames = ms_beetwen_frames;
        this->frames = frames;
        this->animated = true;

        initTextureAndSprite(texture_file);
    }

    Object(std::string name, int pos_x, int pos_y, std::string texture_file){

        this->name = name;
        this->pos_x = pos_x;
        this->pos_y = pos_y;

        initTextureAndSprite(texture_file);
    }

    Object& operator = (const Object& ref){

        name = ref.name;
        pos_x = ref.pos_x;
        pos_y = ref.pos_y;

        texture = ref.texture;
        sprite = ref.sprite;
        sprite.setTexture(texture);

        current_frame = ref.current_frame;
        animated = ref.animated;
        frames = ref.frames;
        ms_beetwen_frames = ref.ms_beetwen_frames;

        elapsed_time = ref.elapsed_time;

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

        current_frame = ref.current_frame;
        animated = ref.animated;
        frames = ref.frames;
        ms_beetwen_frames = ref.ms_beetwen_frames;

        elapsed_time = ref.elapsed_time;

    }

    void update(sf::Time& deltaTime){

        if(animated){

            elapsed_time += deltaTime;

            if(elapsed_time.asMilliseconds() > ms_beetwen_frames){

                if(current_frame >= frames - 1)
                    current_frame = 0;
                else
                    current_frame++;

                int width = texture.getSize().x / frames;
                int height = texture.getSize().y;

                int start_x = width * current_frame;

                this->sprite.setTextureRect(sf::IntRect(start_x, 0, width, height));

                elapsed_time = sf::Time::Zero;
            }
        }
    }

protected:
    virtual void draw (sf::RenderTarget& target, sf::RenderStates) const override {

        target.draw(sprite);
    }


private:

    void initTextureAndSprite(std::string texture_file){

        if(this->texture.loadFromFile(texture_file))
        {
            this->sprite.setTexture(texture);
            this->sprite.setPosition(pos_x, pos_y);
        }
        else
            std::cerr << "failed to load the texture" << std::endl;

        if(animated){

            int x = 0;
            int y = 0;
            int x_max = texture.getSize().x / frames;
            int y_max = texture.getSize().y;

            this->sprite.setTextureRect(sf::IntRect(x, y, x_max, y_max));
        }
    }

    std::string name;
    int pos_x = 0;
    int pos_y = 0;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Time elapsed_time;
    int ms_beetwen_frames = 0;
    int frames = 1;
    int current_frame = 0;

    bool animated = false;

};


#endif //SFML_TEST_OBJECT_HPP
