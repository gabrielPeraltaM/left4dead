//
// Created by ignacio on 6/11/23.
//

#ifndef SDL_PRUEBA_SENDER_H
#define SDL_PRUEBA_SENDER_H

#include <SDL2pp/SDL2pp.hh>

#include "KeyboardHandler.h"
#include "common_src/socket.h"
#include "common_src/thread.h"
using namespace SDL2pp;

class Sender : public Thread{
private:
    bool &running;
    Socket &socket;
    KeyboardHandler keyboardHandler;
    uint8_t action = 0;
    //uint8_t previous_action = 0;
public:
    Sender(Socket &socket, bool &was_closed);
    void run() override;
};


#endif //SDL_PRUEBA_SENDER_H
