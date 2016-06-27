//
// Created by Anthony REY on 25/06/2016.
//

#include "LevelLoader.hpp"

Scene *LevelLoader::generateDataFromLevelFile(std::string levelFile) {

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

Scene *LevelLoader::generateScene(pt::ptree& tree, std::list<std::string> include_files) {

    providen_values = generateIncludeData(include_files);

    Scene* scene = new Scene();
    walk(tree, "level", *scene);
    scene->addPlayer(player);
    return scene;
}

std::map<std::string, std::string> LevelLoader::generateIncludeData(std::list<std::string>& include_files) {

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

void LevelLoader::walk(pt::ptree& tree, std::string key, Scene& scene) {
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
                        if(node_type == "starting-position"){

                            auto x = getAttribute<int>("pos_x", v);
                            auto y = getAttribute<int>("pos_y", v);

                            player.setPosX(x);
                            player.setPosY(y);
                        }
                        if(node_type == "object"){

                            auto obj_name = getAttributeAsString("name", v);
                            auto sprite = getAttributeAsString("sprite", v);
                            auto pos_y = getAttribute<int>("pos_y", v);
                            auto pos_x = getAttribute<int>("pos_x", v);

                            try{

                                auto frames = getAttribute<int>("frames", v);
                                auto ms = getAttribute<int>("ms", v);

                                Object obj(obj_name, pos_x, pos_y, sprite, frames, ms);
                                scene.addObject(obj);
                            }
                            catch(boost::exception & e)
                            {
                                //if no frames / ms (optional)
                                Object obj(obj_name, pos_x, pos_y, sprite);
                                scene.addObject(obj);
                            }
                        }
                    }

                    walk(v.second, new_key + node_type, scene);
                }
}

std::string LevelLoader::getAttributeAsString(std::string attribute, pt::ptree::value_type &v) {

    auto attr = v.second.get<std::string>("<xmlattr>."+attribute);
    return provideAndTranslate(attr);
}

std::string LevelLoader::getValue(pt::ptree::value_type &v) {
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

LevelLoader::LevelLoader(TranslationReader& translation_reader,
                         TxtConfReader& configuration_reader,
                         Object& player)
        : translation_reader(translation_reader), configuration_reader(configuration_reader), player(player) {
}