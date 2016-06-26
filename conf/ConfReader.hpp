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
#include <array>
#include <map>
#include <algorithm>
#include "../exceptions/Exception.hpp"

namespace pt = boost::property_tree;

class TxtConfReader {

public:

    void loadConfiguration(){

        pt::ptree tree;
        pt::ini_parser::read_ini(CONFIG_FILE, tree);

        try{

            for(int i = 0; i < key_count; ++i){

                std::string retrieved_key = tree.get<std::string>(keys[i]);
                config_values.insert(std::pair<std::string, std::string>(keys[i], retrieved_key));
            }
        }
        catch( boost::exception & e ){
            throw Exception("No such key in " + CONFIG_FILE);
        }
    }

    std::map<std::string, std::string>& getConfigurationValues(){
        return config_values;
    };

    std::string getDefaultTranslationFile() {

        auto translation_dir = config_values[TRANSLATION_DIR];
        auto default_dct_filename = config_values[DEFAULT_DCT];
        auto default_lang = config_values[DEFAULT_LANG];
        auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

        return translation_dir + "/" + default_dct_filename+ default_lang + "." + default_conf_type;
    }

    std::string getStartingLevel() {

        auto translation_dir = config_values[LEVELS_DIR];
        auto default_level_filename = config_values[STARTING_LEVEL];
        auto default_conf_type = config_values[DEFAULT_CONF_TYPE];

        return translation_dir +"/"+ default_level_filename + "." + default_conf_type;
    }

    std::string getDefaultFont() {
        auto fonts_dir = config_values[FONTS_DIR];
        auto default_font = config_values[DEFAULT_FONT];

        return fonts_dir + "/" + default_font;
    }

    std::string addPathAndTypeToInclude(std::string name){

        auto path =  config_values[LEVELS_DIR] + "/" + name + "."  + config_values[DEFAULT_CONF_TYPE];
        path.erase(remove_if(path.begin(),path.end(),isspace),path.end());

        return path;
    }

    std::string getAppName()
    {
        return config_values[GAME_NAME];
    }

    ~TxtConfReader(){

    }

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

    //LEVEL section
    const std::string STARTING_LEVEL= "levels.starting-level";


    //FONTS section
    const std::string DEFAULT_FONT ="fonts.default-font";


private:

    const std::string CONFIG_FILE = "./data/config/default.conf_txt";
    static const int key_count = 11;
    std::array<std::string, key_count> keys = {ESCAPE_CHAR, DEFAULT_DCT, DEFAULT_LANG,
                                                TRANSLATION_DIR, LEVELS_DIR, ACTIONS_DIR,
                                                DEFAULT_CONF_TYPE, GAME_NAME, STARTING_LEVEL,
                                               DEFAULT_FONT, FONTS_DIR};

    std::map<std::string, std::string> config_values;
};


#endif //SFML_TEST_TXTCONFREADER_HPP
