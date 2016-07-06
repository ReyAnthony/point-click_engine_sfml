//
// Created by Anthony REY on 06/07/2016.
//

#ifndef SFML_TEST_SPEECHPANEL_HPP
#define SFML_TEST_SPEECHPANEL_HPP


#include <iosfwd>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class SpeechPanel : public sf::Drawable {

public:

    SpeechPanel(std::string default_font_path){
        font.loadFromFile(default_font_path);

        text.setCharacterSize(30);
        text.setPosition(10,10);
        text.setColor(sf::Color::White);
        text.setFont(font);
    }

    void setSentences(std::vector<std::string> sentences){
        this->sentences = sentences;
        current_sentence_index = 0;

        is_visible = true;

        if(!sentences.empty()){
            text.setString(sentences[current_sentence_index]);
        }

    }

    void goToNextSentence(){

        current_sentence_index++;
        if( current_sentence_index < sentences.size()){
            text.setString(sentences[current_sentence_index]);
        }
        else{
            current_sentence_index = 0;
            is_visible = false;
        }


    }

    bool isVisible(){
        return is_visible;
    }

private:

    void draw(sf::RenderTarget& target, sf::RenderStates) const {

        if(is_visible){

            auto width = target.getSize().x;
            auto height = target.getSize().y;

            sf::RectangleShape back_panel(sf::RectangleShape(sf::Vector2f(width, height)));
            back_panel.setFillColor(sf::Color::Black);

            target.draw(back_panel);
            target.draw(text);
        }

    }

    std::vector<std::string> sentences;
    int current_sentence_index = 0;

    sf::Text text;
    sf::Font font;

    bool is_visible;
};


#endif //SFML_TEST_SPEECHPANEL_HPP
