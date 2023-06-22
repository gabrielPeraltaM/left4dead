//
// Created by gabriel on 21/06/23.
//

#include "Witch.h"

#define WITCH_ZOMBIE_RANGE 120
#define SCREAM_NUMBER 52

Witch::Witch(int pos_x, int pos_y, std::map<int, Character*> &zombies) : Zombie(pos_x, pos_y),
                                                                         zombies(zombies),
                                                                         dist(0, 200) {}

void Witch::interact() {
    int scream_number = dist(rd);
    if (scream_number == SCREAM_NUMBER) {
        scream();
    }
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
