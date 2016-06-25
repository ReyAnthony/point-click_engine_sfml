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
#include "../game/Scene.hpp"
#include "../translations/TranslationReader.hpp"
#include "../conf/ConfReader.hpp"
#include "../game/Object.hpp"

namespace pt = boost::property_tree;

class LevelLoader {

public:

    LevelLoader(TranslationReader& translation_reader,
                TxtConfReader& configuration_reader)
            : translation_reader(translation_reader), configuration_reader(configuration_reader){
    }

    Scene generateDataFromLevelFile(std::string levelFile){

        pt::ptree tree;
        pt::read_xml(levelFile, tree);

        std::list<std::string> include_files;

        BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child(""))
        {

            auto node_type = v.first;
            if(node_type != "" && node_type == "include")
            {
                auto include_file_with_path = configuration_reader.addPathAndTypeToInclude(v.second.data());
                include_files.push_back(include_file_with_path);
            }
        }

        return generateScene(tree, include_files);
    }

private:

    Scene generateScene(pt::ptree& tree, std::list<std::string> include_files){

        providen_values = generateIncludeData(include_files);

        Scene scene;
        walk(tree, "level", scene);
        return scene;
    }

    std::map<std::string, std::string> generateIncludeData(std::list<std::string>& include_files){

        std::map<std::string, std::string> providen_values;

        for(auto file: include_files){

            pt::ptree tree;
            pt::read_xml(file, tree);

            BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child(""))
            {
                auto node_type = v.first;
                if(node_type != "" && node_type == "provide"){
                    auto name = v.second.get<std::string>("<xmlattr>.name");
                    providen_values.insert(std::pair<std::string, std::string>(name, v.second.data()));
                }
            }
        }

        return providen_values;
    }


    void walk(pt::ptree& tree, std::string key, Scene& scene)
    {
        std::string new_key;

        if(!key.empty()){
            new_key = key + ".";
        }

        BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child(""))
        {

            auto node_type = v.first;
            if(node_type !=""){
                if(node_type == "level"){
                    
                    auto level_name = getAttributeAsString("name", v);
                    scene.setName(level_name);
                }
                if(node_type == "background"){

                    auto background = getValue(v);
                    scene.addBackground(background);
                }
                if(node_type == "object"){

                    auto obj_name = getAttributeAsString("name", v);
                    auto sprite = getAttributeAsString("sprite", v);
                    auto pos_y = getAttribute<int>("pos_y", v);
                    auto pos_x = getAttribute<int>("pos_x", v);

                    Object obj(obj_name, pos_x, pos_y, sprite);
                    scene.addObject(obj);
                }
            }

            walk(v.second, new_key + node_type, scene);
        }
    }

    template <class T>
    T getAttribute(std::string attribute, pt::ptree::value_type &v){

        auto attr = v.second.get<T>("<xmlattr>."+attribute);
        return attr;
    }

    //TODO specialize for string
    std::string getAttributeAsString(std::string attribute, pt::ptree::value_type &v){

        auto attr = v.second.get<std::string>("<xmlattr>."+attribute);
        return provideAndTranslate(attr);
    }

    std::string getValue(pt::ptree::value_type &v){
        return provideAndTranslate(v.second.data());
    }

    std::string provideAndTranslate(std::string value){

        boost::trim(value);

        if(providen_values.count(value)){
            value = providen_values[value];
            boost::trim(value);
        }

        if(value.find(translation_escape_char) != std::string::npos)
        {
            boost::erase_all(value, translation_escape_char);
            value = translation_reader.getTranslationFromKey(value);
        }

        return value;
    }

    TranslationReader& translation_reader;
    TxtConfReader& configuration_reader;
    std::string translation_escape_char = configuration_reader.getConfigurationValues()[configuration_reader.ESCAPE_CHAR];

    std::map<std::string, std::string> providen_values;
};


/*
std::cout << name << std::endl;

typedef std::map<std::string, std::string>::const_iterator MapIterator;
for (MapIterator iter = providen_values.begin(); iter != providen_values.end(); iter++)
{
   std::cout << "Key: " << iter->first << std::endl << "Values:" << iter->second << std::endl;
}
*/

#endif //SFML_TEST_LEVELLOADER_HPP
