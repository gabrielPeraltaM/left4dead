//
// Created by gabriel on 12/06/23.
//

#include "Zombie.h"
#include <cmath>

#define COLLISION_RANGE 20
#define PERCEPTION_RANGE 200
#define ZOMBIE_DAMAGE 4
#define ZOMBIE_LIFE 100

Zombie::Zombie(int pos_x, int pos_y) : Character(ZOMBIE_LIFE, pos_x, pos_y, COLLISION_RANGE, 0),
                                       moving_x(0),
                                       moving_y(0),
                                       target(nullptr) {}

void Zombie::update_move() {
    int distance_x = this->pos_x - target->get_pos_x();
    int distance_y = this->pos_y - target->get_pos_y();
    double distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
    double dir_x = round(distance_x / distance);
    double dir_y = round(distance_y / distance);
    moving_x = (int)dir_x;
    moving_y = (int)dir_y;
}

void Zombie::interact() {
    if (state == DEAD) {
        return;
    }
    if (target && target_collision()) {
        target->receive_damage(ZOMBIE_DAMAGE);
        return;
    }
    pos_x -= moving_x;
    pos_y -= moving_y;
}

void Zombie::check_target(Character *other) {
    if (other == target) {
        update_move();
        return;
    }
    if ((!target || target->is_dead()) && distance_from(other) < PERCEPTION_RANGE) {
        target = other;
        update_move();
    }
}

double Zombie::distance_from(Character *other) const {
    int distance_x = this->pos_x - other->get_pos_x();
    int distance_y = this->pos_y - other->get_pos_y();
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

bool Zombie::target_collision() {
    int distance_x = this->pos_x - target->get_pos_x();
    int distance_y = this->pos_y - target->get_pos_y();
    double distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
    return distance < this->collision_range + target->get_collision_range();
}

bool Zombie::collision(Character *other, int pos_x, int pos_y) {
    return false;
}

void Zombie::move(int move_x, int move_y) {
}

void Zombie::receive_damage(int damage) {
    if (state == DEAD) {
        return;
    }
    life -= damage;
    if (life <= 0) {
        life = 0;
        state = DEAD;
    }
}

void Zombie::shoot(std::map<int, Character *> &enemies) {}

void Zombie::reload() {}

void Zombie::attack(std::map<int, Character*>& enemies) {}
