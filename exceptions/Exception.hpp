//
// Created by Anthony REY on 25/06/2016.
//

#ifndef SFML_TEST_NOSUCHCONFTYPE_HPP
#define SFML_TEST_NOSUCHCONFTYPE_HPP


#include <iosfwd>
#include <string>

class Exception {

public:

    Exception(std::string error_message);
    std::string getErrorMessage();

private:
    std::string error_message;

};


#endif //SFML_TEST_NOSUCHCONFTYPE_HPP
