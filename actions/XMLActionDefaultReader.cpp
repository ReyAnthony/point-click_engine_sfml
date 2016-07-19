//
// Created by Anthony REY on 18/07/2016.
//

#include "XMLActionDefaultReader.hpp"

XMLActionDefaultReader::XMLActionDefaultReader(TxtConfReader& conf_reader, TranslationReader& translation_reader)
        : translation_reader(translation_reader) {

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
        auto action = new Action(sentences);
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

XMLActionDefaultReader::~XMLActionDefaultReader() {
    for(auto val : actions){
        delete val.second;
    }
}

std::map<GUIActionsType, Action *> XMLActionDefaultReader::getActions() {
    std::map<GUIActionsType, Action *> to_map;
    for(auto val : actions){
        to_map.insert(std::pair<GUIActionsType, Action*>(val.first, new Action(*val.second)));
    }

    return to_map;
}

std::string XMLActionDefaultReader::translate(std::string value) {
    if(value.find(translation_escape_char) != std::string::npos)
    {
        boost::erase_all(value, translation_escape_char);
        value = translation_reader.getTranslationFromKey(value);
    }

    return value;
}