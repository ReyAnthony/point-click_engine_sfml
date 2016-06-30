//
// Created by Anthony REY on 25/06/2016.
//

#include "Object.hpp"
#include "../exceptions/Exception.hpp"

Object::Object() {

}

Object::Object(std::string name, int pos_x, int pos_y, std::string texture_file, int frames, int ms_beetwen_frames, int y_limit) {

    this->name = name;

    this->ms_beetwen_frames = ms_beetwen_frames;
    this->frames = frames;
    this->y_limit = y_limit;

    if(frames > 1)
        this->animated = true;

    initTextureAndSprite(texture_file);
    sprite.setPosition(pos_x, pos_y);
}

Object &Object::operator=(const Object& ref) {

    name = ref.name;

    texture = ref.texture;
    sprite = ref.sprite;
    sprite.setTexture(texture);

    current_frame = ref.current_frame;
    animated = ref.animated;
    frames = ref.frames;
    ms_beetwen_frames = ref.ms_beetwen_frames;

    y_limit = ref.y_limit;

    elapsed_time = ref.elapsed_time;

    return *this;
}

Object::Object(const Object& ref) {
    name = ref.name;

    texture = ref.texture;
    sprite = ref.sprite;
    sprite.setTexture(texture);

    current_frame = ref.current_frame;
    animated = ref.animated;
    frames = ref.frames;
    ms_beetwen_frames = ref.ms_beetwen_frames;

    y_limit = ref.y_limit;


    elapsed_time = ref.elapsed_time;

}

void Object::update(sf::Time& deltaTime) {

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

void Object::setPosX(int pos_x) {
    sprite.setPosition(pos_x, sprite.getPosition().y);
}

void Object::setPosY(int pos_y) {
    sprite.setPosition(sprite.getPosition().x, pos_y);
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates) const {

    target.draw(sprite);
}

void Object::initTextureAndSprite(std::string texture_file) {

    if(this->texture.loadFromFile(texture_file))
    {
        this->sprite.setTexture(texture);
    }
    else
       throw Exception("Failed to load the texture " + texture_file);

    if(animated){

        int x = 0;
        int y = 0;
        int x_max = texture.getSize().x / frames;
        int y_max = texture.getSize().y;

        this->sprite.setTextureRect(sf::IntRect(x, y, x_max, y_max));
    }
}

int Object::getPosY() {
    return sprite.getPosition().y;
}

int Object::getPosX() {
    return sprite.getPosition().x;
}

int Object::getYLimit() {
    return y_limit;
}

int Object::getHeight() {
    return texture.getSize().y;
}

int Object::getWidth() {
    return texture.getSize().x;
}

void Object::notify(sf::Event& event, sf::RenderTarget& renderTarget) {
    if(event.type == sf::Event::MouseButtonPressed){

        //FIXME TAKE INTO ACCOUNT GLOBAL BOUNDS

        auto x = event.mouseButton.x;
        auto y = event.mouseButton.y;

        sf::Vector2i absolute_position (x, y);
        auto relative_position = renderTarget.mapPixelToCoords(absolute_position);

        if(sprite.getGlobalBounds().contains(relative_position)){

            std::cout << name << " clicked" << std::endl;
        }
    }
}