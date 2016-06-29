//
// Created by Anthony REY on 29/06/2016.
//

#ifndef SFML_TEST_ACTIONONOBJECT_HPP
#define SFML_TEST_ACTIONONOBJECT_HPP

#include "LoaderAction.hpp"

class ActionOnObject : public LoaderAction {

    void action(pt::ptree::value_type v, Scene &scene, LevelLoader& loader, std::string node_type) override {

        if(node_type == "object"){

            auto obj_name = loader.getAttributeAsTranslatedString("name", v);
            auto sprite = loader.getAttributeAsTranslatedString("sprite", v);
            auto pos_y = loader.getAttribute<int>("pos_y", v);
            auto pos_x = loader.getAttribute<int>("pos_x", v);

            //optional
            auto frames = loader.getAttributeWithDefaultValue("frames", v, 1);
            auto ms = loader.getAttributeWithDefaultValue("ms", v, 0);
            auto y_limit = loader.getAttributeWithDefaultValue("y_limit", v, -5000);

            Object obj(obj_name, pos_x, pos_y, sprite, frames, ms, y_limit);
            scene.addObject(obj);
        }
    }

};


#endif //SFML_TEST_ACTIONONOBJECT_HPP
