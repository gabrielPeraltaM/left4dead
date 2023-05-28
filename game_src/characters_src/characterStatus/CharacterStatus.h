//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_CHARACTERSTATUS_H
#define LEFT4DEAD_CHARACTERSTATUS_H

enum class State {
    IDLE,
    WALK,
    RUN,
    ATTACK,
    HURT,
    DEAD,
    SHOOT,
    RELOAD,
};

struct CharacterStatus {
    State state = State::IDLE;
    int health;
    int x;
    int y;
    bool flip = false;
    int attackCooldown = 0;
};

#endif //LEFT4DEAD_CHARACTERSTATUS_H
