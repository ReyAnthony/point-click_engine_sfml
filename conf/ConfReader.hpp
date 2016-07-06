//
// Created by Anthony REY on 24/06/2016.
//

#ifndef SFML_TEST_TXTCONFREADER_HPP
#define SFML_TEST_TXTCONFREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <set>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <boost/exception/diagnostic_information.hpp>
#include "../exceptions/Exception.hpp"
#include "../events/GUIActionType.hpp"


namespace pt = boost::property_tree;

class TxtConfReader {

public:

    void loadConfiguration();

    std::string getDefaultConfType();
    std::string getDefaultTranslationFile();
    std::string getStartingLevel();
    unsigned int getFramerate();
    std::string getDefaultFontPath();
    std::string prependLevelPathAndAppendFileType(std::string name);
    std::string getAppName();
    std::string getTranslationEscapeChar();
    std::string getPlayerName();
    std::string getPlayerSpritePath();
    int getPlayerMsBeetwenEachFrames();
    int getPlayerFrames();
    std::string getButtonPath(GUIActionsType actionType);

private:

    std::string generatedFullButtonFilePath(std::string filename);

    //TRANSLATIONS section
    const std::string ESCAPE_CHAR = "translations.translation-escape-char";
    const std::string DEFAULT_DCT = "translations.default-dct-file-name";
    const std::string DEFAULT_LANG = "translations.default-lang";

    //PATHS section
    const std::string TRANSLATION_DIR = "paths.translations-dir";
    const std::string LEVELS_DIR = "paths.levels-dir";
    const std::string ACTIONS_DIR = "paths.actions-dir";
    const std::string FONTS_DIR = "paths.fonts-dir";

    //CONFIG section
    const std::string DEFAULT_CONF_TYPE = "config.default-conf-type";
    const std::string GAME_NAME = "config.game-name";
    const std::string FRAME_RATE = "config.framerate";

    //LEVEL section
    const std::string STARTING_LEVEL= "levels.starting-level";

    //FONTS section
    const std::string DEFAULT_FONT ="fonts.default-font";

    //PLAYER section
    const std::string FRAME_MS = "player.ms";
    const std::string SPRITE = "player.sprite";
    const std::string NAME = "player.name";
    const std::string FRAMES = "player.frames";


    const std::string CONFIG_FILE = "./data/config/default.conf_txt";
    std::list<std::string> keys = {ESCAPE_CHAR, DEFAULT_DCT, DEFAULT_LANG,
                                   TRANSLATION_DIR, LEVELS_DIR, ACTIONS_DIR,
                                   DEFAULT_CONF_TYPE, GAME_NAME, STARTING_LEVEL,
                                   DEFAULT_FONT, FONTS_DIR, FRAME_RATE, FRAME_MS,
                                    SPRITE, NAME, FRAMES};

    std::map<std::string, std::string> config_values;

    const std::string GOTO_BUTT = "GOTO_BUTT";
    const std::string TALK_BUTT = "TALK_BUTT";
    const std::string GRAB_BUTT = "GRAB_BUTT";
    const std::string SEE_BUTT = "SEE_BUTT";
    const std::string USE_BUTT = "USE_BUTT";

    std::map<GUIActionsType , std::string> buttons_path;
};


#endif //SFML_TEST_TXTCONFREADER_HPP
