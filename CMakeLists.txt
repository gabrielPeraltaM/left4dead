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
        client/game/GameProtocol/ReceiverProtocol.h)
target_link_libraries(client PUBLIC SDL2pp)

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
        server_src/ActionQueue.cpp
        server_src/Action.h
        server_src/StateQueue.cpp
        server_src/Groups.cpp
        server_src/game/Character.cpp
        server_src/game/Map.cpp
        server_src/ActionMove.cpp
        server_src/game/GameState.cpp
        server_src/Login.cpp
        server_src/ServerProtocol.cpp
        server_src/Receiver.cpp
        server_src/Sender.cpp
        server_src/Commands.cpp
        server_src/game/Zombie.cpp
        server_src/State.cpp
        server_src/game/Survivor.cpp
        server_src/ActionShoot.cpp
        server_src/ActionReload.cpp
        server_src/ActionAttack.cpp
        server_src/game/Witch.cpp
        server_src/game/Idf.cpp
        server_src/game/Scout.cpp
        server_src/ActionStart.cpp)

# Google test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)