//
// Created by Anthony REY on 25/06/2016.
//

#ifndef SFML_TEST_LEVELLOADER_HPP
#define SFML_TEST_LEVELLOADER_HPP

#include <iosfwd>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <list>
#include <map>

#include "../game/GameScene.hpp"
#include "../translations/TranslationReader.hpp"
#include "../conf/ConfReader.hpp"
#include "../game/Object.hpp"
#include "../events/EventDispatcher.hpp"
#include "../game/Action.hpp"
#include "../actions/XMLActionDefaultReader.hpp"
#include "../events/LevelSwitchObserver.hpp"
#include "../pathfind/Collider.h"


namespace pt = boost::property_tree;

class LevelLoader {

public:

    LevelLoader(TranslationReader& translation_reader,
                TxtConfReader& configuration_reader,
                Object& player, EventDispatcher& event_dispatcher,
                ActionPanel& action_panel,
                SpeechPanel& speech_panel,
                XMLActionDefaultReader& xml_action_default_reader,
                LevelSwitchObserver& level_switch_observer,
                std::map<std::string, GameScene*>& level_map);

    GameScene *generateGameSceneFromLevelFile(std::string level_path, std::string level_name);

private:

    template <class T>
    T getAttribute(std::string attribute, pt::ptree::value_type &v){

        auto attr = v.second.get<T>("<xmlattr>."+attribute);
        return attr;
    }

    template <class T>
    T getAttributeWithDefaultValue(std::string attribute, pt::ptree::value_type &v, T defaultValue){

        auto attr = v.second.get("<xmlattr>."+attribute, defaultValue);
        return attr;
    }

    std::string getAttributeAsTranslatedString(std::string attribute, pt::ptree::value_type &v);
    std::string getNodeValueAsTranslatedString(pt::ptree::value_type &v);


    GameScene * generateScene(pt::ptree& tree, std::list<std::string> include_files);
    std::map<std::string, std::string> generateIncludeData(std::list<std::string>& include_files);
    void walk(pt::ptree& tree, GameScene & scene);

    std::string provideAndTranslate(std::string value);
    std::string level_name;

    EventDispatcher& event_dispatcher;
    LevelSwitchObserver& level_switch_observer;

    ActionPanel& action_panel;
    TranslationReader& translation_reader;
    TxtConfReader& configuration_reader;
    XMLActionDefaultReader& xml_action_default_reader;
    Object& player;
    SpeechPanel& speech_panel;
    std::string translation_escape_char = configuration_reader.getTranslationEscapeChar();

    std::map<std::string, std::string> providen_values;
    std::map<std::string, GameScene*>& level_map;
};

#endif //SFML_TEST_LEVELLOADER_HPP
