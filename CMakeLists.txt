cmake_minimum_required(VERSION 3.3)
project(sfml_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -F /Library/Frameworks -framework sfml-window -framework sfml-graphics -framework sfml-system")

set(SOURCE_FILES main.cpp exceptions/KeyException.cpp exceptions/KeyException.hpp translations/TranslationReader.cpp translations/TranslationReader.hpp translations/XMLTranslationReader.cpp translations/XMLTranslationReader.hpp game/Scene.cpp game/Scene.hpp game/SharedDataPool.cpp game/SharedDataPool.hpp conf/ConfReader.cpp conf/ConfReader.hpp conf/ConfReader.cpp conf/ConfReader.hpp exceptions/NoSuchConfType.cpp exceptions/NoSuchConfType.hpp levels/LevelLoader.cpp levels/LevelLoader.hpp)

add_executable(sfml_test ${SOURCE_FILES})

add_custom_command(TARGET sfml_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:sfml_test>/data)