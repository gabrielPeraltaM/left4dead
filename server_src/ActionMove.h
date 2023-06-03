//
// Created by gabriel on 01/06/23.
//

#ifndef LEFT4DEAD_ACTION_MOVE_H
#define LEFT4DEAD_ACTION_MOVE_H

#include "Action.h"
#include "./game/Map.h"
#include "State.h"
#include <memory>

class ActionMove : public Action {
    int move_x;
    int move_y;

   public:
    ActionMove(int player_id, int move_x, int move_y);

    std::shared_ptr<State> execute(Map &map) override;
};

#endif  // LEFT4DEAD_ACTION_MOVE_H