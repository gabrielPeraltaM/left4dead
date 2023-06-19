//
// Created by gabriel on 19/06/23.
//

#ifndef LEFT4DEAD_ACTION_RELOAD_H
#define LEFT4DEAD_ACTION_RELOAD_H

#include "Action.h"

class ActionReload : public Action {
public:
    void execute(Map &map) override;
};

#endif //LEFT4DEAD_ACTION_RELOAD_H
