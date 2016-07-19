//
// Created by Anthony REY on 25/06/2016.
//

#include "LevelLoader.hpp"
#include "../events/LevelSwitchObserver.hpp"

LevelLoader::LevelLoader(TranslationReader& translation_reader,
                         TxtConfReader& configuration_reader,
                         Object& player,
                         EventDispatcher& event_dispatcher,
                         ActionPanel& action_panel,
                         SpeechPanel& speech_panel,
                         XMLActionDefaultReader& xml_action_default_reader,
                         LevelSwitchObserver& level_switch_observer,
                         std::map<std::string, GameScene*>& level_map)
        :
          translation_reader(translation_reader),
          configuration_reader(configuration_reader),
          player(player),
          event_dispatcher(event_dispatcher),
          action_panel(action_panel),
          speech_panel(speech_panel),
          xml_action_default_reader(xml_action_default_reader),
          level_switch_observer(level_switch_observer),
          level_map(level_map){
}

GameScene *LevelLoader::generateGameSceneFromLevelFile(std::string level_path, std::string level_name) {

    this->level_name = level_name;

    pt::ptree tree;
    pt::read_xml(level_path, tree);

    std::list<std::string> include_files;

    for(pt::ptree::value_type &v : tree.get_child(""))
    {
        auto node_type = v.first;
        if(node_type != "" && node_type == "include")
        {
            //Translation is not needed
            auto node_value = getNodeValueAsTranslatedString(v);
            auto include_file_with_path = configuration_reader.prependLevelPathAndAppendFileType(node_value);
            include_files.push_back(include_file_with_path);
        }
    }

    return generateScene(tree, include_files);
}

GameScene *LevelLoader::generateScene(pt::ptree& tree, std::list<std::string> include_files) {

    providen_values = generateIncludeData(include_files);
    GameScene * scene = new GameScene(player, action_panel, speech_panel);
    scene->registerObserver(level_switch_observer);
    level_map.insert(std::pair<std::string, GameScene*>(level_name, scene));
    walk(tree, *scene);
    //on truande, vu que c'est le dernier executé (recursif) on remet le player à la place desginée dans ce niveau ..
    scene->resetPlayerToDefaultPosition();
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
                auto content = getNodeValueAsTranslatedString(v);
                providen_values.insert(std::pair<std::string, std::string>(name, content));
            }
        }
    }

    return providen_values;
}

void LevelLoader::walk(pt::ptree& tree, GameScene & scene) {

    for(pt::ptree::value_type &v : tree.get_child(""))
    {
        //FIXME should add an XLST verification of the schema
        auto node_type = v.first;

        if(node_type !=""){

            if(node_type == "level"){

                auto level_name = getAttributeAsTranslatedString("name", v);
                scene.setName(level_name);
            }

            if(node_type == "background"){

                auto background = getNodeValueAsTranslatedString(v);
                scene.setBackground(background);
            }

            if(node_type == "starting-position"){

                auto x = getAttribute<int>("pos_x", v);
                auto y = getAttribute<int>("pos_y", v);
                scene.setDefaultPos(x, y);
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
                auto default_actions = xml_action_default_reader.getActions();
                obj->setActions(default_actions);
                scene.addObject(*obj);
            }

            if(node_type == "collider"){

                auto& obj = scene.getLastInsertedObject();

                auto x = getAttributeWithDefaultValue<int>("x", v, 0);
                auto y = getAttributeWithDefaultValue<int>("y", v, obj.getYLimit());
                auto width = getAttributeWithDefaultValue<int>("width", v, obj.getWidth());
                auto height = getAttributeWithDefaultValue<int>("height", v, 0);

                Collider collider(width, height, x + obj.getPosX() ,y + obj.getPosY());
                obj.setCollider(collider);
            }

            if(node_type == "talk" || node_type == "see" || node_type == "use"){

                auto parent_node_type = node_type;

                if(node_type == "see" || node_type == "talk"){

                    std::vector<std::string> sentences;
                    for(pt::ptree::value_type &v : v.second)
                    {
                        node_type = v.first;
                        if(node_type == "say")
                            sentences.push_back(getNodeValueAsTranslatedString(v));
                    }

                    Object& last_inserted_object = scene.getLastInsertedObject();

                    if(parent_node_type == "see"){
                        Action* see_action = new Action(sentences);
                        last_inserted_object.addAction(SEE, see_action);
                    }
                    else {
                        Action* talk_action = new Action(sentences);
                        last_inserted_object.addAction(TALK, talk_action);
                    }
                }
                else if(node_type == "grab"){
                    Object& last_inserted_object = scene.getLastInsertedObject();
                    last_inserted_object.addAction(GRAB, new Action(GRAB));
                }
                else if (node_type == "use"){
                    for(pt::ptree::value_type &v : v.second)
                    {
                        node_type = v.first;
                        if(node_type == "goto" && parent_node_type == "use"){

                            auto level_file = v.second.data();

                            //if the level is not in the map (otherwize infinite inclusions)
                            if(level_map.find(level_file) == level_map.end()){

                                LevelLoader* loader = new LevelLoader(translation_reader,
                                                                      configuration_reader,
                                                                      player,
                                                                      event_dispatcher,
                                                                      action_panel,
                                                                      speech_panel,
                                                                      xml_action_default_reader,
                                                                      level_switch_observer,
                                                                      level_map);

                                generateGameSceneFromLevelFile(configuration_reader.getLevelPath(level_file), level_file);
                                delete loader;
                            }

                            Object& last_inserted_object = scene.getLastInsertedObject();
                            last_inserted_object.addAction(USE, new Action(level_file));
                            //only one goto, so we break
                            break;
                        }
                    }
                }
            }
        }

        walk(v.second, scene);
    }
}

std::string LevelLoader::getAttributeAsTranslatedString(std::string attribute, pt::ptree::value_type &v) {

    auto attr = v.second.get<std::string>("<xmlattr>."+attribute);
    return provideAndTranslate(attr);
}

std::string LevelLoader::getNodeValueAsTranslatedString(pt::ptree::value_type &v) {
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
