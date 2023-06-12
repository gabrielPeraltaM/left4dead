//
// Created by ignacio on 6/11/23.
//

#ifndef SDL_PRUEBA_SENDER_H
#define SDL_PRUEBA_SENDER_H


#include "common_src/thread.h"
#include "common_src/socket.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class Sender : public Thread{
private:
    const Uint8 *state = nullptr;
    bool &running;
    Socket &socket;
public:
    Sender(Socket &socket, bool &was_closed);
    void run() override;
};


#endif //SDL_PRUEBA_SENDER_H
