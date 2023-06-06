//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_ACTION_H
#define LEFT4DEAD_ACTION_H

#include "./game/Map.h"
#include "State.h"
#include <memory>

class Action {
   public:
    int player_id = -1;
    virtual std::shared_ptr<State> execute(Map &map) = 0;
};

#endif //LEFT4DEAD_ACTION_H
