//
// Created by Anthony REY on 14/07/2016.
//
#include "JSONTranslationReader.hpp"



JSONTranslationReader::JSONTranslationReader(std::string filename) {
    this->filename = filename;
}
std::string JSONTranslationReader::getTranslationFromKey(std::string key) {

    nlohmann::json j = nlohmann::json::parse(key);
    std::cout << j;

    return "";
}