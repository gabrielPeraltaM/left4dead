//
// Created by gabriel on 01/06/23.
//

#ifndef LEFT4DEAD_ACTION_MOVE_H
#define LEFT4DEAD_ACTION_MOVE_H

#include "Action.h"
#include "server_src/State.h"
#include "server_src/game/Map.h"

class ActionMove : public Action {
    int move_x;
    int move_y;
    bool isRunning = false;

   public:
    ActionMove(int move_x, int move_y);
    ActionMove(int move_x, int move_y, bool isRunning);

    void execute(Map &map) override;
};

#endif  // LEFT4DEAD_ACTION_MOVE_H
