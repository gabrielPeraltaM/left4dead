//
// Created by gabriel on 19/06/23.
//

#include "ActionAttack.h"

void ActionAttack::execute(Map &map) {
    map.attack(player_id);
}
