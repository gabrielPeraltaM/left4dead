//
// Created by gabriel on 30/05/23.
//

#include "Character.h"
#include <cmath>

Character::Character(int life, int pos_x, int pos_y,
                     int collision_range, int ammo) : life(life),
                                                      pos_x(pos_x),
                                                      pos_y(pos_y),
                                                      collision_range(collision_range),
                                                      state(NOT),
                                                      ammo(ammo) {
}

int Character::get_life() const {
    return life;
}

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

int Character::get_ammo() const {
    return ammo;
}

void Character::start_shooting() {
    state = SHOOTING;
}

void Character::stop_shooting() {
    if (state != SHOOTING) {
        return;
    }
    state = NOT;
}

bool Character::is_dead() const {
    return state == DEAD;
}
