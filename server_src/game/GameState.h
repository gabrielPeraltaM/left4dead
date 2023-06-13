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
    explicit GameState(int limit_y);

    void add_character(int id, int collision_range);

    void receive_action(const std::shared_ptr<Action>& action);

    std::shared_ptr<State> update();
};

#endif  // LEFT4DEAD_GAME_STATE_H
