cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(left4dead LANGUAGES CXX VERSION 0.10 DESCRIPTION "Left 4 Dead Grupo 8")

# SDL
find_package(SDL2pp REQUIRED)

# Compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Resources
add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/resources")

# define targets
add_executable(cliente
        client_src/main.cpp
        client_src/layout/game/Game.cpp
        client_src/layout/game/Game.h
        client_src/characters_src/characterData/CharacterData.h
        client_src/characters_src/characterData/players/IDFData.h
        client_src/characters_src/characterData/players/P90Data.h
        client_src/characters_src/characterData/players/ScoutData.h
        client_src/characters_src/characterData/enemies/ZombieData.h
        client_src/characters_src/characterData/enemies/JumperData.h
        client_src/characters_src/characterData/enemies/SpearData.h
        client_src/characters_src/characterData/enemies/VenomData.h
        client_src/characters_src/characterData/enemies/WitchData.h
        client_src/characters_src/characterTextures/CharacterTexture.h
        client_src/characters_src/characterTextures/players/IDFTextures.h
        client_src/characters_src/characterTextures/enemies/ZombieTextures.h
        client_src/characters_src/characterStatus/players/PlayerStatus.h
        client_src/characters_src/characterStatus/CharacterStatus.h
        client_src/characters_src/character/Character.cpp
        client_src/characters_src/character/Character.h
        client_src/characters_src/character/players/Player.cpp
        client_src/characters_src/character/players/Player.h
        client_src/characters_src/character/enemies/Enemy.cpp
        client_src/characters_src/character/enemies/Enemy.h
        client_src/characters_src/character/players/IDF.cpp
        client_src/characters_src/character/players/IDF.h
        client_src/characters_src/character/enemies/Zombie.cpp
        client_src/characters_src/character/enemies/Zombie.h
        client_src/characters_src/character/enemies/Jumper.cpp
        client_src/characters_src/character/enemies/Jumper.h
        client_src/characters_src/character/enemies/Witch.cpp
        client_src/characters_src/character/enemies/Witch.h
        client_src/characters_src/character/enemies/Spear.cpp
        client_src/characters_src/character/enemies/Spear.h
        client_src/characters_src/character/enemies/Venom.cpp
        client_src/characters_src/character/enemies/Venom.h
        client_src/characters_src/characterTextures/players/P90Textures.h
        client_src/characters_src/character/players/P90.cpp
        client_src/characters_src/character/players/P90.h
        client_src/characters_src/characterTextures/players/PlayerTexture.h
        client_src/characters_src/characterTextures/enemies/EnemyTexture.h
        client_src/characters_src/characterTextures/players/ScoutTextures.h
        client_src/layout/game/GameInterface.cpp
        client_src/layout/game/GameInterface.h
        client_src/layout/game/GameStatus.cpp
        client_src/layout/game/GameStatus.h
        client_src/layout/game/GameStorage.cpp
        client_src/layout/game/GameStorage.h
        client_src/client/Client.cpp
        client_src/client/Client.h
        client_src/client/ActionsParser.cpp
        client_src/client/ActionsParser.h
        client_src/client/Protocol.cpp
        client_src/client/Protocol.h
        common_src/socket.h
        common_src/socket.cpp
        common_src/thread.h
        common_src/thread.cpp
        common_src/liberror.h
        common_src/liberror.cpp
        common_src/resolvererror.h
        common_src/resolvererror.cpp
        common_src/resolver.h
        common_src/resolver.cpp
        client_src/layout/game/GameRenderer.cpp client_src/layout/game/GameRenderer.h client_src/layout/game/GameProtocol.cpp client_src/layout/game/GameProtocol.h)

target_link_libraries(cliente PUBLIC SDL2pp::SDL2pp)

add_executable(server server_src/main.cpp
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
        server_src/Groups.cpp
        server_src/game/Character.cpp server_src/game/Map.cpp server_src/ActionMove.cpp server_src/game/GameState.cpp server_src/Login.cpp server_src/ServerProtocol.cpp server_src/Receiver.cpp server_src/Sender.cpp server_src/Commands.cpp)
target_link_libraries(server SDL2pp::SDL2pp)
