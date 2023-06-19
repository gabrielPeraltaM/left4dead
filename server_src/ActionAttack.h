//
// Created by gabriel on 19/06/23.
//

#ifndef LEFT4DEAD_ACTION_ATTACK_H
#define LEFT4DEAD_ACTION_ATTACK_H

#include "Action.h"

class ActionAttack : public Action {
    void execute(Map &map) override;
};

#endif //LEFT4DEAD_ACTION_ATTACK_H
