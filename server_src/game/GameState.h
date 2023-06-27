//
// Created by gabriel on 30/05/23.
//

#ifndef LEFT4DEAD_GAME_STATE_H
#define LEFT4DEAD_GAME_STATE_H

#include <memory>

#include "../State.h"
#include "Map.h"
#include "server_src/actions/Action.h"

class GameState {
    Map map;

   public:
    explicit GameState(int limit_y);

    void add_character(int player_id, int character_type);

    void receive_action(const std::shared_ptr<Action>& action);

    std::shared_ptr<State> update();
};

#endif  // LEFT4DEAD_GAME_STATE_H
