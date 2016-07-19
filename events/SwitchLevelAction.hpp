//
// Created by Anthony REY on 19/07/2016.
//

#ifndef SFML_TEST_SCENEACTIONS_HPP
#define SFML_TEST_SCENEACTIONS_HPP

#include <iosfwd>
#include <string>

class SwitchLevelAction {

public:
    SwitchLevelAction(std::string new_level){
        this->new_level = new_level;
    }

    std::string getLevel() const{
        return new_level;
    }

private:
   std::string new_level;

};


#endif //SFML_TEST_SCENEACTIONS_HPP
