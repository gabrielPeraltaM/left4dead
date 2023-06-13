//
// Created by gabriel on 12/06/23.
//

#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H

#include "Character.h"

class Zombie : private Character {
    int move_x;
    int move_y;
    Character *target;

public:
    Zombie(int pos_x, int pos_y);

    void update_move();

    void interact();

    void check_target(Character *other);

private:
    double distance_from(Character *other) const;

    bool target_collision();
};

#endif //LEFT4DEAD_ZOMBIE_H
