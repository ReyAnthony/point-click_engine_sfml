//
// Created by Anthony REY on 24/06/2016.
//

#include "ConfReader.hpp"

void TxtConfReader::loadConfiguration() {

    pt::ptree tree;

    try{
        pt::ini_parser::read_ini(CONFIG_FILE, tree);
    }
    catch(boost::exception &e){
        throw Exception(boost::diagnostic_information(e));
    }

    try{

        for(auto key : keys){

            std::string retrieved_key = tree.get<std::string>(key);
            config_values.insert(std::pair<std::string, std::string>(key, retrieved_key));
        }
    }
    catch(boost::exception & e){
        throw Exception("No such key in " + CONFIG_FILE);
    }

    buttons_path.insert(std::pair<GUIActionsType , std::string>(GOTO, generatedFullButtonFilePath(GOTO_BUTT)));
    buttons_path.insert(std::pair<GUIActionsType , std::string>(GRAB, generatedFullButtonFilePath(GRAB_BUTT)));
    buttons_path.insert(std::pair<GUIActionsType , std::string>(SEE, generatedFullButtonFilePath(SEE_BUTT)));
    buttons_path.insert(std::pair<GUIActionsType , std::string>(USE, generatedFullButtonFilePath(USE_BUTT)));
    buttons_path.insert(std::pair<GUIActionsType , std::string>(TALK, generatedFullButtonFilePath(TALK_BUTT)));

}

std::string TxtConfReader::getDefaultConfType() {
    return config_values[DEFAULT_CONF_TYPE];
}

std::string TxtConfReader::getDefaultTranslationFile() {

    auto translation_dir = config_values[TRANSLATION_DIR];
    auto default_dct_filename = config_values[DEFAULT_DCT];
    auto default_lang = config_values[DEFAULT_LANG];
    auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

    return translation_dir + "/" + default_dct_filename+ default_lang + "." + default_conf_type;
}

std::string TxtConfReader::getStartingLevelPath() {

    auto translation_dir = config_values[LEVELS_DIR];
    auto default_level_filename = config_values[STARTING_LEVEL];
    auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

    return translation_dir +"/"+ default_level_filename + "." + default_conf_type;
}

std::string TxtConfReader::getLevelPath(std::string level) {

    auto translation_dir = config_values[LEVELS_DIR];
    auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

    return translation_dir +"/"+ level + "." + default_conf_type;
}

unsigned int TxtConfReader::getFramerate() {
    return std::stoul(config_values[FRAME_RATE]);
}

std::string TxtConfReader::getDefaultFontPath() {
    auto fonts_dir = config_values[FONTS_DIR];
    auto default_font = config_values[DEFAULT_FONT];

    return fonts_dir + "/" + default_font;
}

std::string TxtConfReader::prependLevelPathAndAppendFileType(std::string name) {

    auto path =  config_values[LEVELS_DIR] + "/" + name + "."  + config_values[DEFAULT_CONF_TYPE];
    path.erase(remove_if(path.begin(),path.end(),isspace),path.end());

    return path;
}

std::string TxtConfReader::getAppName() {

    return config_values[GAME_NAME];
}

std::string TxtConfReader::getTranslationEscapeChar() {
    return config_values[ESCAPE_CHAR];
}

std::string TxtConfReader::getPlayerName() {
    return config_values[NAME];
}

std::string TxtConfReader::getPlayerSpritePath() {
    return config_values[SPRITE];
}

int TxtConfReader::getPlayerMsBeetwenEachFrames() {
    return (unsigned  int) std::stoul(config_values[FRAME_MS]);
}

int TxtConfReader::getPlayerFrames() {
    return (unsigned int) std::stoul(config_values[FRAMES]);
}

std::string TxtConfReader::generatedFullButtonFilePath(std::string filename) {

    return config_values[ACTIONS_DIR] + "/" +  filename + "_" + config_values[DEFAULT_LANG] + ".png";
}

std::string TxtConfReader::getButtonPath(GUIActionsType type) {
    return buttons_path[type];
}

std::string TxtConfReader::getDefaultActionConfPath() {

    auto actions_dir = config_values[ACTIONS_DIR];
    auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

    return actions_dir + "/" + "actions_default" + "." + default_conf_type;
}