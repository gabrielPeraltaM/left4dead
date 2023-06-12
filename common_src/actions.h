//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_PRUEBA_ACTIONS_H
#define SDL_PRUEBA_ACTIONS_H

enum actions : int {
    IDLE = 0x04,
    MOVE_UP = 0x05,
    MOVE_DOWN = 0x06,
    MOVE_LEFT = 0x07,
    MOVE_RIGHT = 0x08,
    SHOOT = 0x09,
    ATTACK = 0x0A,
    RELOAD = 0x0B,
    MOVE_UP_LEFT,
    MOVE_UP_RIGHT,
    MOVE_DOWN_LEFT,
    MOVE_DOWN_RIGHT,
    HURT,
    DIE,
};

#endif //SDL_PRUEBA_ACTIONS_H