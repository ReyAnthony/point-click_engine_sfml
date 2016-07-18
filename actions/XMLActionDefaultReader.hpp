//
// Created by Anthony REY on 18/07/2016.
//

#ifndef SFML_TEST_XMLACTIONDEFAULTREADER_HPP
#define SFML_TEST_XMLACTIONDEFAULTREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <map>
#include <iostream>
#include "../events/GUIActionType.hpp"
#include "../game/Action.hpp"

namespace pt = boost::property_tree;

class XMLActionDefaultReader {

public:
    XMLActionDefaultReader(std::string config_file){

        pt::ptree tree;
        pt::read_xml(config_file, tree);
        actions.insert(std::pair<GUIActionsType , Action*>(NOOP, new Action(NOOP)));

        for(pt::ptree::value_type &v : tree.get_child(""))
        {
            auto action_type = v.first;

            std::vector<std::string> sentences;
            sentences.push_back(v.second.data());
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
                std::cout << v.first << "," << v.second.data() << std::endl;
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
    std::map<GUIActionsType, Action *> actions;
};


#endif //SFML_TEST_XMLACTIONDEFAULTREADER_HPP
