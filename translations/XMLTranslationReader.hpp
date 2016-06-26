//
// Created by Anthony REY on 24/05/2016.
//

#ifndef SFML_TEST_XMLTRANSLATIONREADER_HPP
#define SFML_TEST_XMLTRANSLATIONREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include "TranslationReader.hpp"
#include "../exceptions/Exception.hpp"

namespace pt = boost::property_tree;

class XMLTranslationReader : public TranslationReader
{
public:
    XMLTranslationReader(std::string filename);
    std::string getTranslationFromKey(std::string key) override;

private:
    std::string filename;
};


#endif //SFML_TEST_XMLTRANSLATIONREADER_HPP
