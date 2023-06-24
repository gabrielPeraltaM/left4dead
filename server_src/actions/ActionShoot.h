//
// Created by gabriel on 13/06/23.
//

#ifndef LEFT4DEAD_ACTION_SHOOT_H
#define LEFT4DEAD_ACTION_SHOOT_H

#include "Action.h"

class ActionShoot : public Action {
public:
    void execute(Map &map) override;
};

#endif //LEFT4DEAD_ACTION_SHOOT_H
