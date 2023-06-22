//
// Created by gabriel on 21/06/23.
//

#include "Witch.h"

#define WITCH_ZOMBIE_RANGE 120
#define WITCH_COLLISION_RANGE 80
#define SCREAM_NUMBER 52

Witch::Witch(int pos_x, int pos_y,
             std::map<int, Character*> &zombies) : Zombie(pos_x, pos_y, WITCH_COLLISION_RANGE, WITCH),
                                                   zombies(zombies),
                                                   dist(0, 200) {}

void Witch::interact() {
    if (state == DEAD) {
        return;
    }
    int scream_number = dist(rd);
    if (scream_number == SCREAM_NUMBER) {
        scream();
        return;
    }
    if (target && target_collision()) {
        return;
    }
    pos_x -= moving_x;
    pos_y -= moving_y;
}

void Witch::scream() {
    //state = ATTACKING;
    for (auto element : zombies) {
        auto *zombie = element.second;
        if (zombie->is_dead()) {
            continue;
        }
        if (Character::distance(zombie, pos_x, pos_y) > WITCH_ZOMBIE_RANGE) {
            zombie->witch_interact(pos_x, pos_y);
            continue;
        }
        zombie->witch_interact(zombie->get_pos_x(), zombie->get_pos_y());
    }
}
