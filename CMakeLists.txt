cmake_minimum_required(VERSION 3.3)
project(sfml_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -F /Library/Frameworks -framework sfml-window -framework sfml-graphics -framework sfml-system ")

set(SOURCE_FILES main.cpp exceptions/Exception.cpp exceptions/Exception.hpp translations/TranslationReader.cpp translations/TranslationReader.hpp translations/XMLTranslationReader.cpp translations/XMLTranslationReader.hpp game/GameScene.cpp game/GameScene.hpp conf/ConfReader.cpp conf/ConfReader.hpp conf/ConfReader.cpp conf/ConfReader.hpp levels/LevelLoader.cpp levels/LevelLoader.hpp game/Object.cpp game/Object.hpp exceptions/ExceptionScene.cpp exceptions/ExceptionScene.hpp Application.cpp Application.hpp main.hpp events/EventDispatcher.cpp events/EventDispatcher.hpp events/Observable.cpp events/Observable.hpp events/Observer.cpp events/Observer.hpp game/Player.cpp game/Player.hpp game/AbstractScene.cpp game/AbstractScene.hpp events/GUIActionType.hpp game/Action.cpp game/Action.hpp game/action_panel/ActionPanel.cpp game/action_panel/ActionPanel.hpp game/action_panel/Button.cpp game/action_panel/Button.hpp game/speech_panel/SpeechPanel.cpp game/speech_panel/SpeechPanel.hpp translations/JSONTranslationReader.cpp translations/JSONTranslationReader.hpp actions/XMLActionDefaultReader.cpp actions/XMLActionDefaultReader.hpp game/Action.cpp)

add_executable(sfml_test ${SOURCE_FILES})

add_custom_command(TARGET sfml_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:sfml_test>/data)