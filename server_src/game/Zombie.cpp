//
// Created by gabriel on 12/06/23.
//

#include "Zombie.h"
#include <cmath>

#define PERCEPTION_RANGE 350
#define ZOMBIE_DAMAGE 4
#define ZOMBIE_LIFE 100
#define ATTACK_DELAY 10

Zombie::Zombie(int pos_x,
               int pos_y,
               int collision_range,
               int hurt_range, Type type) : Character(ZOMBIE_LIFE, pos_x, pos_y,
                                                      collision_range, hurt_range, 0, type),
                                            moving_x(0),
                                            moving_y(0),
                                            target(nullptr),
                                            delay(0) {}

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
    if (state == DEAD || state == ATTACKING) {
        return;
    }
    /*if (state == ATTACKING && delay < 10) {
        ++delay;
        return;
    }*/
    //delay = 0;
    //state = NOT;
    if (target && target_collision()) {
        target->receive_damage(ZOMBIE_DAMAGE);
        state = ATTACKING;
        return;
    }
    pos_x -= moving_x;
    pos_y -= moving_y;
}

void Zombie::check_target(Character *survivor) {
    if (survivor == target) {
        update_move();
        return;
    }
    if ((!target || target->is_dead()) && distance_from(survivor) < PERCEPTION_RANGE) {
        target = survivor;
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

void Zombie::witch_interact(int witch_pos_x, int witch_pos_y) {
    if (state == DEAD || target) {
        return;
    }
    int distance_x = this->pos_x - witch_pos_x;
    int distance_y = this->pos_y - witch_pos_y;
    double distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
    double dir_x = round(distance_x / distance);
    double dir_y = round(distance_y / distance);
    moving_x = (int)dir_x;
    moving_y = (int)dir_y;
}

void Zombie::reset_state() {
    if (state == DEAD) {
        return;
    }
    if (state == ATTACKING && delay < ATTACK_DELAY) {
        ++delay;
        return;
    }
    delay = 0;
    state = NOT;
}

void Zombie::stop_moving() {
    if (state == DEAD || target) {
        return;
    }
    moving_x = 0;
    moving_y = 0;
}

void Zombie::shoot(std::map<int, Character *> &enemies) {}

void Zombie::reload() {}

void Zombie::attack(std::map<int, Character*>& enemies) {}
