//
// Created by gabriel on 13/06/23.
//

#include "ActionShoot.h"

void ActionShoot::execute(Map &map) {
    map.shoot(player_id);
}
