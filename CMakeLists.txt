cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(left4dead LANGUAGES CXX VERSION 0.10 DESCRIPTION "Left 4 Dead Grupo 8")

# SDL
find_package(SDL2pp REQUIRED)

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

# Compilation flags
set(CMAKE_CXX_STANDARD 17)

# Resources
add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/resources")

#[[
add_executable(left4dead server_src/main.cpp
                        server_src/server.cpp
                        common_src/liberror.cpp
                        common_src/resolvererror.cpp
                        common_src/resolver.cpp
                        common_src/socket.cpp
                        server_src/Acceptor.cpp
                        server_src/ClientHandler.cpp
                        server_src/Matches.cpp
                        server_src/Match.cpp
                        common_src/thread.cpp
                        common_src/protocol.cpp
                        server_src/GroupMatch.cpp
                        server_src/ActionQueue.cpp
                        server_src/Action.h
                        server_src/State.h
                        server_src/StateQueue.cpp
                        server_src/Player.cpp
                        server_src/Groups.cpp
                        server_src/Players.cpp)
target_link_libraries(left4dead SDL2pp::SDL2pp)
]]

# define targets
add_executable(lesson00 game_src/main.cpp game_src/characters/player/Player.cpp game_src/characters/player/Player.h game_src/characters/Character.cpp game_src/characters/Character.h game_src/layout/game/Game.cpp game_src/layout/game/Game.h game_src/characters/zombie/Zombie.cpp game_src/characters/zombie/Zombie.h game_src/characters/player/IDF.cpp game_src/characters/player/IDF.h game_src/characters/player/P90.cpp game_src/characters/player/P90.h game_src/characters/player/Scout.cpp game_src/characters/player/Scout.h game_src/characters/zombie/Jumper.cpp game_src/characters/zombie/Jumper.h game_src/characters/zombie/Spear.cpp game_src/characters/zombie/Spear.h game_src/characters/zombie/Venom.cpp game_src/characters/zombie/Venom.h game_src/characters/zombie/Witch.cpp game_src/characters/zombie/Witch.h game_src/layout/menu/menu.cpp game_src/layout/menu/menu.h game_src/layout/menu/menu.ui)
target_link_libraries(lesson00 PUBLIC SDL2pp::SDL2pp)
target_link_libraries(lesson00 PUBLIC Qt6::Widgets)
