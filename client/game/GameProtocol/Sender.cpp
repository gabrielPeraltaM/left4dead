//
// Created by ignacio on 6/11/23.
//

#include "Sender.h"
#include "common_src/actions.h"

Sender::Sender(Socket &socket, bool &running) : socket(socket), running(running) {}

void Sender::run() {
    bool was_closed = false;
    uint8_t action;
    while (running) {
        // Delay
        SDL_Delay(1000 / 60);

        state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_R]) {
            action = RELOAD;
            socket.sendall(&action, 1, &was_closed);
            continue;
        }

        if (state[SDL_SCANCODE_SPACE]) {
            action = SHOOT;
            socket.sendall(&action, 1, &was_closed);
            continue;
        }

        if (state[SDL_SCANCODE_LCTRL]) {
            action = ATTACK;
            socket.sendall(&action, 1, &was_closed);
            continue;
        }

        // Move
        int direction = 0;
        if (state[SDL_SCANCODE_A]) {
            direction |= 1;
        } else if (state[SDL_SCANCODE_D]) {
            direction |= 2;
        }

        // Move vertically
        if (state[SDL_SCANCODE_W]) {
            direction |= 4;
        } else if (state[SDL_SCANCODE_S]) {
            direction |= 8;
        }

        switch (direction) {
            case 0:
                //action = IDLE;
                //socket.sendall(&action, 1, &was_closed);
                break;
            case 1:
                action = MOVE_LEFT;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 2:
                action = MOVE_RIGHT;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 4:
                action = MOVE_UP;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 8:
                action = MOVE_DOWN;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 5:
                action = MOVE_UP_LEFT;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 6:
                action = MOVE_UP_RIGHT;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 9:
                action = MOVE_DOWN_LEFT;
                socket.sendall(&action, 1, &was_closed);
                break;
            case 10:
                action = MOVE_DOWN_RIGHT;
                socket.sendall(&action, 1, &was_closed);
                break;
            default:
                break;
        }
    }
}
