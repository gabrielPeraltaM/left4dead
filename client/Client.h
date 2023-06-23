//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_CLIENT_H
#define SDL_PRUEBA_CLIENT_H

#include "common_src/socket.h"

class Client {
    Socket peer;
    bool was_closed = false;
    bool host = false;
public:
    Client(const char *hostname, const char *port);
    void run();
};


#endif //SDL_PRUEBA_CLIENT_H
