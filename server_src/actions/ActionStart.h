//
// Created by gabriel on 23/06/23.
//

#ifndef LEFT4DEAD_ACTION_START_H
#define LEFT4DEAD_ACTION_START_H

#include "Action.h"

class ActionStart : public Action {
    void execute(Map &map) override;
};

#endif //LEFT4DEAD_ACTION_START_H
