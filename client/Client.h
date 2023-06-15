//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_CLIENT_H
#define SDL_PRUEBA_CLIENT_H

#include "common_src/socket.h"

class Client {
    Socket peer;
    bool was_closed = false;
public:
    Client(const char *hostname, const char *port);
    void getFirstAction();
    uint32_t createGame(std::string &scenarioName);
    uint8_t joinGame(uint32_t gameId);
    uint8_t getPlayerId();
    void startGame();
};


#endif //SDL_PRUEBA_CLIENT_H
