//
// Created by gabriel on 30/05/23.
//

#include "Character.h"
#include <math.h>

Character::Character(int pos_x,
                     int pos_y,
                     int collision_range) : pos_x(pos_x),
                                            pos_y(pos_y),
                                            collision_range(collision_range) {}

void Character::move(int move_x, int move_y) {
    pos_x += move_x;
    pos_y += move_y;
}

bool Character::collision(Character *other, int move_x, int move_y) {
    auto distance = this->distance(other, pos_x + move_x, pos_y + move_y);
    return distance < this->collision_range + other->collision_range;
}

int Character::get_pos_x() {
    return pos_x;
}

int Character::get_pos_y() {
    return pos_y;
}

double Character::distance(Character *other, int new_pos_x, int new_pos_y) {
    int distance_x = other->pos_x - new_pos_x;
    int distance_y = other->pos_y - new_pos_y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}
