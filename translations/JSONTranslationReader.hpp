//
// Created by Anthony REY on 14/07/2016.
//

#ifndef SFML_TEST_JSONTRANSLATIONREADER_HPP
#define SFML_TEST_JSONTRANSLATIONREADER_HPP

#include <iosfwd>
#include <string>
#include "../src/json.hpp"
#include "TranslationReader.hpp"
#include "../exceptions/Exception.hpp"
#include <boost/exception/diagnostic_information.hpp>


class JSONTranslationReader : public TranslationReader
{
public:
    JSONTranslationReader(std::string filename);
    std::string getTranslationFromKey(std::string key) override;

private:
    std::string filename;
};

#endif //SFML_TEST_JSONTRANSLATIONREADER_HPP
