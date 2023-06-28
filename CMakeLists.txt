cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(left4dead LANGUAGES CXX VERSION 0.10 DESCRIPTION "Left 4 Dead Grupo 8")

# SDL
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
set(SDL2PP_WITH_MIXER YES)
add_subdirectory(SDL2pp)
find_package(SDL2pp REQUIRED)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Resources
add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/resources")

# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/home/$ENV{USER}/Qt/6.5.0/gcc_64") # TODO: Change this to your Qt installation path
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Client
add_executable(client
        client/main.cpp
        client/game/Game.cpp
        client/game/GameRenderer/GameRenderer.cpp
        common_src/thread.cpp
        common_src/socket.cpp
        common_src/liberror.cpp
        common_src/resolver.cpp
        common_src/resolvererror.cpp
        client/characters/Character.cpp
        common_src/actions.h
        client/Client.cpp
        client/game/GameProtocol/Receiver.cpp
        client/game/GameProtocol/Receiver.h
        client/game/GameRenderer/BackgroundRenderer.cpp
        client/game/GameRenderer/BackgroundRenderer.h
        client/game/GameRenderer/UIRenderer.cpp
        client/game/GameRenderer/UIRenderer.h
        client/game/GameProtocol/Sender.cpp
        client/game/GameProtocol/Sender.h
        client/game/GameRenderer/PlayerRenderer.cpp
        client/game/GameRenderer/PlayerRenderer.h
        client/game/GameProtocol/KeyboardHandler.cpp
        client/game/GameProtocol/KeyboardHandler.h
        client/game/GameProtocol/ReceiverProtocol.cpp
        client/game/GameProtocol/ReceiverProtocol.h
        client/ClientProtocol.cpp
        client/ClientProtocol.h
        client/Menu/createroom.cpp
        client/Menu/createroom.ui
        client/Menu/joinroom.cpp
        client/Menu/joinroom.ui
        client/Menu/mainwindow.cpp
        client/Menu/mainwindow.ui
        client/Menu/room.cpp
        client/Menu/room.ui
        client/game/GameMonitor/CharactersQueue.cpp
        client/game/GameMonitor/CharactersQueue.h
        client/Menu/leaderboard.cpp
        client/Menu/leaderboard.ui
        client/Menu/options.cpp
        client/Menu/options.ui client/StateQueue.cpp)

target_link_libraries(client PUBLIC SDL2pp Qt6::Core
        Qt6::Gui
        Qt6::Widgets)

# Server
add_executable(server server_src/main.cpp
        server_src/server.cpp
        common_src/liberror.cpp
        common_src/resolvererror.cpp
        common_src/resolver.cpp
        common_src/socket.cpp
        server_src/Acceptor.cpp
        server_src/ClientHandler.cpp
        server_src/Matches.cpp
        server_src/Player.cpp
        common_src/thread.cpp
        common_src/protocol.cpp
        server_src/GroupMatch.cpp
        server_src/actions/ActionQueue.cpp
        server_src/actions/Action.h
        server_src/StateQueue.cpp
        server_src/Groups.cpp
        server_src/game/Character.cpp
        server_src/game/Map.cpp
        server_src/actions/ActionMove.cpp
        server_src/game/GameState.cpp
        server_src/Login.cpp
        server_src/ServerProtocol.cpp
        server_src/Receiver.cpp
        server_src/Sender.cpp
        server_src/Commands.cpp
        server_src/game/Zombie.cpp
        server_src/State.cpp
        server_src/game/Survivor.cpp
        server_src/actions/ActionShoot.cpp
        server_src/actions/ActionReload.cpp
        server_src/actions/ActionAttack.cpp
        server_src/game/Witch.cpp
        server_src/game/Idf.cpp
        server_src/game/Scout.cpp
        server_src/actions/ActionStart.cpp server_src/game/P90.cpp)

install(TARGETS client server DESTINATION bin)

# Google test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#[===[
sh install.sh
ngrok
yaml cpp
sudo install sdl
estadisticas
]===]