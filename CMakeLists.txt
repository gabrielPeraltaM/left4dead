cmake_minimum_required(VERSION 3.24)
project(left4dead)

set(CMAKE_CXX_STANDARD 17)

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
