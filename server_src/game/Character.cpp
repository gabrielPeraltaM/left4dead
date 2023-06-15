//
// Created by gabriel on 30/05/23.
//

#include "Character.h"
#include <cmath>

Character::Character(int pos_x, int pos_y,
                     int collision_range) : pos_x(pos_x),
                                            pos_y(pos_y),
                                            collision_range(collision_range),
                                            state(IDLE) {}

int Character::get_pos_x() const {
    return pos_x;
}

int Character::get_pos_y() const {
    return pos_y;
}

int Character::get_collision_range() const {
    return collision_range;
}

double Character::distance(Character *other, int new_pos_x, int new_pos_y) {
    int distance_x = other->pos_x - new_pos_x;
    int distance_y = other->pos_y - new_pos_y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

int Character::get_state() const {
    return state;
}

int Character::get_shooting() const {
    return state;
}

void Character::star_shooting() {
    state = SHOOT;
}

void Character::stop_shooting() {
    state = IDLE;
}
