//
// Created by Anthony REY on 24/05/2016.
//

#ifndef SFML_TEST_TRANSLATIONREADER_HPP
#define SFML_TEST_TRANSLATIONREADER_HPP

#include <iostream>

class TranslationReader
{

public:
    virtual std::string getTranslationFromKey(std::string key) = 0;

protected:
    const std::string NAME_ATTR = "name";
    const std::string DICTIONNARY = "dict";
};


#endif //SFML_TEST_TRANSLATIONREADER_HPP
