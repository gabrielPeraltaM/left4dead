//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_ACTION_H
#define LEFT4DEAD_ACTION_H

#include "./game/Map.h"
#include "State.h"
#include <memory>

class Action {
   protected:
    int player_id;

   public:
    explicit Action(int player_id) : player_id(player_id) {}

    virtual std::shared_ptr<State> execute(Map &map) = 0;
};

#endif //LEFT4DEAD_ACTION_H
