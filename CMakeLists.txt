cmake_minimum_required(VERSION 3.3)
project(sfml_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -F /Library/Frameworks -framework sfml-window -framework sfml-graphics -framework sfml-system ")

set(SOURCE_FILES main.cpp exceptions/Exception.cpp exceptions/Exception.hpp translations/TranslationReader.cpp translations/TranslationReader.hpp translations/XMLTranslationReader.cpp translations/XMLTranslationReader.hpp game/GameScene.cpp game/GameScene.hpp conf/ConfReader.cpp conf/ConfReader.hpp conf/ConfReader.cpp conf/ConfReader.hpp levels/LevelLoader.cpp levels/LevelLoader.hpp game/Object.cpp game/Object.hpp exceptions/ExceptionScene.cpp exceptions/ExceptionScene.hpp Application.cpp Application.hpp main.hpp events/EventDispatcher.cpp events/EventDispatcher.hpp events/Observable.cpp events/Observable.hpp events/Observer.cpp events/Observer.hpp game/Player.cpp game/Player.hpp game/AbstractScene.cpp game/AbstractScene.hpp events/GUIActionType.hpp game/AbstractAction.hpp game/actions/TalkAction.cpp game/actions/TalkAction.hpp game/actions/NoopAction.cpp game/actions/NoopAction.hpp game/actions/SeeAction.cpp game/actions/SeeAction.hpp game/actions/UseAction.cpp game/actions/UseAction.hpp game/actions/GotoAction.cpp game/actions/GotoAction.hpp game/actions/GrabAction.cpp game/actions/GrabAction.hpp game/action_panel/ActionPanel.cpp game/action_panel/ActionPanel.hpp game/action_panel/Button.cpp game/action_panel/Button.hpp)

add_executable(sfml_test ${SOURCE_FILES})

add_custom_command(TARGET sfml_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:sfml_test>/data)