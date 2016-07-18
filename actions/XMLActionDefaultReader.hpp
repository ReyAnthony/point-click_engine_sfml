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
    XMLActionDefaultReader(TxtConfReader& conf_reader, TranslationReader& translation_reader)
            : translation_reader(translation_reader){

        translation_escape_char = conf_reader.getTranslationEscapeChar();

        pt::ptree tree;
        pt::read_xml(conf_reader.getDefaultActionConfPath(), tree);
        actions.insert(std::pair<GUIActionsType , Action*>(NOOP, new Action(NOOP)));

        for(pt::ptree::value_type &v : tree.get_child(""))
        {
            auto action_type = v.first;
            auto text = translate(v.second.data());

            std::vector<std::string> sentences;
            sentences.push_back(text);
            auto action = new Action(TALK, sentences);
            GUIActionsType actionToInsert = NOOP;

            if(action_type == "talk")
              actionToInsert = TALK;
            else if(action_type == "grab")
                actionToInsert = GRAB;
            else if(action_type == "see")
                actionToInsert = SEE;
            else if(action_type == "goto")
                actionToInsert = GOTO;
            else if(action_type == "use")
                actionToInsert = USE;

            if(actionToInsert != NOOP){
                actions.insert(std::pair<GUIActionsType, Action *>(actionToInsert , action));
            }
        }
    }

    ~XMLActionDefaultReader(){
        for(auto val : actions){
            delete val.second;
        }
    }

    std::map<GUIActionsType, Action *> getActions(){
        return actions;
    };
private:

    std::string translation_escape_char;
    std::map<GUIActionsType, Action *> actions;
    TranslationReader& translation_reader;

    std::string translate(std::string value){
        if(value.find(translation_escape_char) != std::string::npos)
        {
            boost::erase_all(value, translation_escape_char);
            value = translation_reader.getTranslationFromKey(value);
        }

        return value;
    }
};


#endif //SFML_TEST_XMLACTIONDEFAULTREADER_HPP
