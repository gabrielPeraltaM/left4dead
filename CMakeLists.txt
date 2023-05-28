cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(left4dead LANGUAGES CXX VERSION 0.10 DESCRIPTION "Left 4 Dead Grupo 8")

# SDL
find_package(SDL2pp REQUIRED)

# Compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Resources
add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/resources")

# define targets
add_executable(left4dead 
        game_src/main.cpp
        game_src/layout/game/Game.cpp
        game_src/layout/game/Game.h
        game_src/characters_src/characterData/CharacterData.h
        game_src/characters_src/characterData/players/IDFData.h
        game_src/characters_src/characterData/players/P90Data.h
        game_src/characters_src/characterData/players/ScoutData.h
        game_src/characters_src/characterData/enemies/ZombieData.h
        game_src/characters_src/characterData/enemies/JumperData.h
        game_src/characters_src/characterData/enemies/SpearData.h
        game_src/characters_src/characterData/enemies/VenomData.h
        game_src/characters_src/characterData/enemies/WitchData.h
        game_src/characters_src/characterTextures/CharacterTexture.h
        game_src/characters_src/characterTextures/players/IDFTextures.h
        game_src/characters_src/characterTextures/enemies/ZombieTextures.h
        game_src/characters_src/characterStatus/players/PlayerStatus.h
        game_src/characters_src/characterStatus/CharacterStatus.h
        game_src/characters_src/character/Character.cpp
        game_src/characters_src/character/Character.h
        game_src/characters_src/character/players/Player.cpp
        game_src/characters_src/character/players/Player.h
        game_src/characters_src/character/enemies/Enemy.cpp
        game_src/characters_src/character/enemies/Enemy.h
        game_src/characters_src/character/players/IDF.cpp
        game_src/characters_src/character/players/IDF.h
        game_src/characters_src/character/enemies/Zombie.cpp
        game_src/characters_src/character/enemies/Zombie.h game_src/characters_src/character/enemies/Jumper.cpp game_src/characters_src/character/enemies/Jumper.h game_src/characters_src/character/enemies/Witch.cpp game_src/characters_src/character/enemies/Witch.h game_src/characters_src/character/enemies/Spear.cpp game_src/characters_src/character/enemies/Spear.h game_src/characters_src/character/enemies/Venom.cpp game_src/characters_src/character/enemies/Venom.h game_src/characters_src/characterTextures/players/P90Textures.h game_src/characters_src/character/players/P90.cpp game_src/characters_src/character/players/P90.h game_src/characters_src/characterTextures/players/PlayerTexture.h game_src/characters_src/characterTextures/enemies/EnemyTexture.h)

target_link_libraries(left4dead PUBLIC SDL2pp::SDL2pp)



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
