//
// Created by Anthony REY on 18/07/2016.
//

#ifndef SFML_TEST_XMLACTIONDEFAULTREADER_HPP
#define SFML_TEST_XMLACTIONDEFAULTREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <map>
#include <iostream>
#include "../events/GUIActionType.hpp"
#include "../game/Action.hpp"
#include "../translations/TranslationReader.hpp"
#include "../conf/ConfReader.hpp"


namespace pt = boost::property_tree;

class XMLActionDefaultReader {

public:
    XMLActionDefaultReader(TxtConfReader& conf_reader, TranslationReader& translation_reader);
    ~XMLActionDefaultReader();
    std::map<GUIActionsType, Action *> getActions();

private:

    std::string translation_escape_char;
    std::map<GUIActionsType, Action *> actions;
    TranslationReader& translation_reader;
    std::string translate(std::string value);
};


#endif //SFML_TEST_XMLACTIONDEFAULTREADER_HPP
