//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H

#include "./ActionQueue.h"
#include "./StateQueue.h"

class Player {
    ActionQueue actions;
    StateQueue states;
};

#endif //LEFT4DEAD_PLAYER_H
