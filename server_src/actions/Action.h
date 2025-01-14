//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_ACTION_H
#define LEFT4DEAD_ACTION_H

#include <memory>

#include "server_src/State.h"
#include "server_src/game/Map.h"

class Action {
   public:
    int player_id = -1;
    virtual void execute(Map &map) = 0;
};

#endif //LEFT4DEAD_ACTION_H
