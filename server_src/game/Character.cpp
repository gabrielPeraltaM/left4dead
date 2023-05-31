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

void Character::move(int x, int y) {
    pos_x += x;
    pos_y += y;
}

bool Character::collision(Character *other, int move_x, int move_y) {
    auto distance = this->distance(move_x, move_y);
    return distance < this->collision_range + other->collision_range;
}

int Character::get_pos_x() {
    return pos_x;
}

int Character::get_pos_y() {
    return pos_y;
}

double Character::distance(int move_x, int move_y) {
    int distance_x = pos_x - move_x;
    int distance_y = pos_y - move_y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}
