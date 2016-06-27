//
// Created by Anthony REY on 25/06/2016.
//

#include "Exception.hpp"

Exception::Exception(std::string error_message) {
    this->error_message = error_message;
}

std::string Exception::getErrorMessage() {
    return error_message;
}