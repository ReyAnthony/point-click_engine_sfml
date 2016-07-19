//
// Created by Anthony REY on 06/07/2016.
//

#include "SpeechPanel.hpp"

SpeechPanel::SpeechPanel(std::string default_font_path) {
    font.loadFromFile(default_font_path);

    text.setCharacterSize(30);
    text.setPosition(10,10);
    text.setColor(sf::Color::White);
    text.setFont(font);
}

void SpeechPanel::setSentences(std::vector<std::string> sentences) {
    this->sentences = sentences;
    current_sentence_index = 0;

    is_visible = true;

    if(!sentences.empty()){
        text.setString(sentences[current_sentence_index]);
    }

}

void SpeechPanel::goToNextSentence() {

    current_sentence_index++;
    if( current_sentence_index < sentences.size()){
        text.setString(sentences[current_sentence_index]);
    }
    else{
        current_sentence_index = 0;
        is_visible = false;
    }


}

bool SpeechPanel::isVisible() {
    return is_visible;
}

void SpeechPanel::draw(sf::RenderTarget& target, sf::RenderStates) const {

    if(is_visible){

        auto width = target.getSize().x;
        auto height = target.getSize().y;

        sf::RectangleShape back_panel(sf::RectangleShape(sf::Vector2f(width, height)));
        back_panel.setFillColor(sf::Color::Black);

        target.draw(back_panel);
        target.draw(text);
    }

}