//
// Created by gabriel on 01/06/23.
//

#ifndef LEFT4DEAD_ACTION_MOVE_H
#define LEFT4DEAD_ACTION_MOVE_H

#include "Action.h"
#include "./game/Map.h"
#include "State.h"

class ActionMove : public Action {
    int move_x;
    int move_y;

   public:
    ActionMove(int move_x, int move_y);

    void execute(Map &map) override;
};

#endif  // LEFT4DEAD_ACTION_MOVE_H
