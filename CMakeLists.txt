cmake_minimum_required(VERSION 3.25)
project(left4dead)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -ggdb -DDEBUG -Wall -fno-inline -pedantic -pedantic-errors -pthread -D _POSIX_C_SOURCE=200809L")

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2pp REQUIRED)


find_package(sdl2 REQUIRED)
find_package(sdl2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

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
                        server_src/Players.cpp game_src/main.cpp)
target_link_libraries(left4dead SDL2pp::SDL2pp)
]]

# define targets
add_executable(lesson00 game_src/main.cpp)
target_link_libraries(lesson00 PUBLIC SDL2pp::SDL2pp)