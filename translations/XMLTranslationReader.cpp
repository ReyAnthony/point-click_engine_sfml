//
// Created by Anthony REY on 24/05/2016.
//

#include "XMLTranslationReader.hpp"

XMLTranslationReader::XMLTranslationReader(std::string filename) {
    this->filename = filename;
}

std::string XMLTranslationReader::getTranslationFromKey(std::string key) {

    pt::ptree tree;
    pt::read_xml(filename, tree);

    BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child(DICTIONNARY))
                {
                    //if the "name" attr of the current tag is the one we look for
                    if(v.second.get<std::string>("<xmlattr>." + NAME_ATTR) == key)
                    {
                        //the value of the tag
                        auto data_to_return = v.second.data();
                        if(data_to_return != "<xmlattr>")
                        {
                            boost::trim(data_to_return);
                            return data_to_return;
                        }
                        break;
                    }
                }

    throw KeyException();
}
