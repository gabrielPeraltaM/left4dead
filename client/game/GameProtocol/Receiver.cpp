//
// Created by ignacio on 6/10/23.
//

#include "Receiver.h"
#include "common_src/actions.h"


Receiver::Receiver(Socket &socket, bool &running, std::vector<Character> &characters) : socket(socket),
                                                                                        running(running),
                                                                                        characters(characters) {
}

void Receiver::run() {
    uint8_t action;
    uint8_t playerId;
    bool was_closed = false;
    while (running) {
        // Receive action
        socket.recvall(&action, sizeof(action), &was_closed);
        if (was_closed) {
            running = false;
            break;
        }
        // Receive id
        socket.recvall(&playerId, sizeof(playerId), &was_closed);
        playerId--;
        if (was_closed) {
            running = false;
            break;
        }

        // Do action
        Character &character = characters.at(playerId);

        switch (action) {
            case actions::MOVE_UP:
                character.move(0, -1);
                break;
            case actions::MOVE_DOWN:
                character.move(0, 1);
                break;
            case actions::MOVE_LEFT:
                character.move(-1, 0);
                break;
            case actions::MOVE_RIGHT:
                character.move(1, 0);
                break;
            case actions::MOVE_DOWN_LEFT:
                character.move(-1, 1);
                break;
            case actions::MOVE_DOWN_RIGHT:
                character.move(1, 1);
                break;
            case actions::MOVE_UP_LEFT:
                character.move(-1, -1);
                break;
            case actions::MOVE_UP_RIGHT:
                character.move(1, -1);
                break;
            case actions::IDLE:
                character.idle();
                break;
            case actions::ATTACK:
                character.attack();
                break;
            case actions::HURT:
                character.hurt();
                break;
            case actions::DIE:
                character.die();
                break;
            case actions::SHOOT:
                character.shoot();
                break;
            case actions::RELOAD:
                character.reload();
                break;
            default:
                break;
        }
    }
}