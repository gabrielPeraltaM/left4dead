//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_RECEIVER_H
#define SDL_PRUEBA_RECEIVER_H


#include "client/characters/Character.h"
#include "common_src/thread.h"
#include "common_src/socket.h"
#include <vector>

class Receiver : public Thread {
private:
    bool &running;
    std::vector<Character> &characters;
    Socket &socket;
public:
    Receiver(Socket &socket, bool &was_closed, std::vector<Character> &characters);
    void run() override;
};


#endif //SDL_PRUEBA_RECEIVER_H
