//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_GAME_STATE_H
#define LEFT4DEAD_GAME_STATE_H

#include "Map.h"
#include "../State.h"
#include "../Action.h"
#include <memory>

class GameState {
    Map map;

   public:
    GameState(int limit_x, int limit_y);

    void add_character(int id, int collision_range);

    std::shared_ptr<State> update(Action action);
};

#endif  // LEFT4DEAD_GAME_STATE_H
