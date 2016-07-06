//
// Created by Anthony REY on 06/07/2016.
//

#ifndef SFML_TEST_SPEECHPANEL_HPP
#define SFML_TEST_SPEECHPANEL_HPP


#include <iosfwd>
#include <vector>
#include <SFML/Graphics.hpp>

class SpeechPanel : public sf::Drawable {

public:

    SpeechPanel(std::string default_font_path){
        font.loadFromFile(default_font_path);

        text.setCharacterSize(30);
        text.setPosition(10,0);
        text.setColor(sf::Color::White);
        text.setFont(font);
    }

    void setSentences(std::vector<std::string> sentences){
        this->sentences = sentences;
        current_sentence = 0;

        is_visible = true;

        if(!sentences.empty())
            text.setString(sentences[current_sentence]);
    }

    bool goToNextSentence(){

        current_sentence++;
        if(sentences.size() <= current_sentence){
            text.setString(sentences[current_sentence]);
            return true;
        }
        return true;
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
    int current_sentence = 0;

    sf::Text text;
    sf::Font font;

    bool is_visible;
};


#endif //SFML_TEST_SPEECHPANEL_HPP
