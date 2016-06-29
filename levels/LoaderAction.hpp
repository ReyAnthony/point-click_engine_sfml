//
// Created by Anthony REY on 28/06/2016.
//

#ifndef SFML_TEST_LOADERACTIONS_HPP
#define SFML_TEST_LOADERACTIONS_HPP

#include "LevelLoader.hpp"

class LoaderAction {

public:
    virtual void action(pt::ptree::value_type v, Scene &scene, LevelLoader& loader, std::string node_type) =0;
    
};


#endif //SFML_TEST_LOADERACTIONS_HPP
