cmake_minimum_required(VERSION 3.16)
project(B_YEP_400_PAR_4_1_indiestudio_gabriel_medoukali)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/)
FIND_PACKAGE(raylib REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/Error)
include_directories(src/GameManager)
include_directories(src/Lib)
include_directories(src/Lib/IU)
include_directories(src/Lib/IU/NonSelectable)
include_directories(src/Lib/IU/Selectable)
include_directories(src/Lib/Map)
include_directories(src/Lib/Map/Movable)
include_directories(src/Lib/Map/Static)
include_directories(src/Parser)

add_executable(bomberman
        src/Error/Error.cpp
        src/Error/Error.hpp
        src/GameManager/Game.cpp
        src/GameManager/Game.hpp
        src/Core/Core.cpp
        src/Core/Core.hpp
        src/Core/CoreMenu.cpp
        src/Audio/Audio.cpp
        src/Audio/Audio.hpp
        src/Lib/Scene/Cam.cpp
        src/Lib/Scene/Cam.hpp
        src/Lib/Scene/Window.cpp
        src/Lib/Scene/Window.hpp
        src/Lib/IU/NonSelectable/ANonSelectable.hpp
        src/Lib/IU/NonSelectable/ANonSelectable.cpp
        src/Lib/IU/NonSelectable/Texture2D.cpp
        src/Lib/IU/NonSelectable/Texture2D.hpp
        src/Lib/IU/NonSelectable/Text.cpp
        src/Lib/IU/NonSelectable/Text.hpp
        src/Lib/IU/NonSelectable/ShapeRect.cpp
        src/Lib/IU/NonSelectable/ShapeRect.hpp
        src/Lib/IU/NonSelectable/ShapeCircle.cpp
        src/Lib/IU/NonSelectable/ShapeCircle.hpp
        src/Lib/IU/Selectable/ASelectable.hpp
        src/Lib/IU/Selectable/ASelectable.cpp
        src/Lib/IU/Selectable/Button.cpp
        src/Lib/IU/Selectable/Button.hpp
        src/Lib/IU/Selectable/InputBox.cpp
        src/Lib/IU/Selectable/InputBox.hpp
        src/Lib/Map/Static/Bonus.cpp
        src/Lib/Map/Static/Bonus.hpp
        src/Lib/IU/AIu.hpp
        src/Lib/IU/AIu.cpp
        src/Lib/Map/Movable/IA.cpp
        src/Lib/Map/Movable/IA.hpp
        src/Lib/Map/Movable/Player.cpp
        src/Lib/Map/Movable/Player.hpp
        src/Lib/Map/Static/Effect.cpp
        src/Lib/Map/Static/Effect.hpp
        src/Lib/Map/Static/Block.cpp
        src/Lib/Map/Static/Block.hpp
        src/Lib/Map/Static/Objects.cpp
        src/Lib/Map/Static/Objects.hpp
        src/Lib/Map/Static/Wall.cpp
        src/Lib/Map/Static/Wall.hpp
        src/Lib/Map/AMap.hpp
        src/Lib/Map/AMap.cpp
        src/Lib/ITransform.hpp
        src/Utils/Timer.cpp
        src/Utils/Timer.hpp
        src/Core/CoreGameIU.cpp
        src/Core/CoreGameIU.hpp
        src/Lib/Map/Static/AnimatedModel.cpp
        src/Lib/Map/Static/AnimatedModel.hpp
        src/main.cpp)

target_link_libraries(bomberman raylib)
