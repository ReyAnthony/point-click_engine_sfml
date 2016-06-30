//
// Created by Anthony REY on 25/06/2016.
//

#include "LevelLoader.hpp"

LevelLoader::LevelLoader(TranslationReader& translation_reader,
                         TxtConfReader& configuration_reader,
                         Object& player, EventDispatcher& event_dispatcher)
        : translation_reader(translation_reader), configuration_reader(configuration_reader),
          player(player), event_dispatcher(event_dispatcher) {
}

GameScene *LevelLoader::generateDataFromLevelFile(std::string levelFile) {

    pt::ptree tree;
    pt::read_xml(levelFile, tree);

    std::list<std::string> include_files;

    for(pt::ptree::value_type &v : tree.get_child(""))
    {

        auto node_type = v.first;
        if(node_type != "" && node_type == "include")
        {
            auto node_value = getNodeValue(v);
            auto include_file_with_path = configuration_reader.prependLevelPathAndAppendFileType(node_value);
            include_files.push_back(include_file_with_path);
        }
    }

    return generateScene(tree, include_files);
}

GameScene *LevelLoader::generateScene(pt::ptree& tree, std::list<std::string> include_files) {

    providen_values = generateIncludeData(include_files);

    GameScene * scene = new GameScene(player);
    walk(tree, *scene);
    return scene;
}

std::map<std::string, std::string> LevelLoader::generateIncludeData(std::list<std::string>& include_files) {

    std::map<std::string, std::string> providen_values;

    for(auto file: include_files){

        pt::ptree tree;
        pt::read_xml(file, tree);

        for(pt::ptree::value_type &v : tree.get_child(""))
        {
            auto node_type = v.first;
            if(node_type != "" && node_type == "provide"){
                auto name = getAttribute<std::string>("name", v);
                auto content = getNodeValue(v);
                providen_values.insert(std::pair<std::string, std::string>(name, content));
            }
        }
    }

    return providen_values;
}

void LevelLoader::walk(pt::ptree& tree, GameScene & scene) {

    for(pt::ptree::value_type &v : tree.get_child(""))
    {

        auto node_type = v.first;

        if(node_type !=""){
            if(node_type == "level"){

                auto level_name = getAttributeAsTranslatedString("name", v);
                scene.setName(level_name);
            }
            if(node_type == "background"){

                auto background = getNodeValue(v);
                scene.addBackground(background);
            }
            if(node_type == "starting-position"){

                auto x = getAttribute<int>("pos_x", v);
                auto y = getAttribute<int>("pos_y", v);

                player.setPosX(x);
                player.setPosY(y);
            }

            if(node_type == "object"){

                auto obj_name = getAttributeAsTranslatedString("name", v);
                auto sprite = getAttributeAsTranslatedString("sprite", v);
                auto pos_y = getAttribute<int>("pos_y", v);
                auto pos_x = getAttribute<int>("pos_x", v);

                //optional
                auto frames = getAttributeWithDefaultValue<int>("frames", v, 1);
                auto ms = getAttributeWithDefaultValue<int>("ms", v, 0);
                auto y_limit = getAttributeWithDefaultValue<int>("y_limit", v, -5000);

                Object* obj = new Object (obj_name, pos_x, pos_y, sprite, frames, ms, y_limit);
                scene.addObject(*obj);
            }

            if(node_type == "collider"){
                Object& lastInsertedObject = scene.getLastInsertedObject();
            }

        }

        walk(v.second, scene);
    }
}

std::string LevelLoader::getAttributeAsTranslatedString(std::string attribute, pt::ptree::value_type &v) {

    auto attr = v.second.get<std::string>("<xmlattr>."+attribute);
    return provideAndTranslate(attr);
}

std::string LevelLoader::getNodeValue(pt::ptree::value_type &v) {
    return provideAndTranslate(v.second.data());
}

std::string LevelLoader::provideAndTranslate(std::string value) {

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
