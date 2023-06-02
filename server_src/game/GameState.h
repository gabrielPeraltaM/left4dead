//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_GAME_STATE_H
#define LEFT4DEAD_GAME_STATE_H

#include "Map.h"
#include "../State.h"
#include "../Action.h"

class GameState {
    Map map;

   public:
    GameState(const int limit_x, const int limit_y);

    ~GameState();

    void add_character(int id, int collision_range);

    State update(Action action);
};

#endif  // LEFT4DEAD_GAME_STATE_H
