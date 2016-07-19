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

    SpeechPanel(std::string default_font_path);
    void setSentences(std::vector<std::string> sentences);
    void goToNextSentence();
    bool isVisible();

private:

    void draw(sf::RenderTarget& target, sf::RenderStates) const;

    std::vector<std::string> sentences;
    int current_sentence_index = 0;

    sf::Text text;
    sf::Font font;

    bool is_visible;
};


#endif //SFML_TEST_SPEECHPANEL_HPP
