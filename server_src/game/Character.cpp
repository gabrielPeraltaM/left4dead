//
// Created by gabriel on 30/05/23.
//

#include "Character.h"
#include <cmath>

#define CHARACTER_LIFE 100
#define DEFAULT_DAMAGE 4
#define MAX_SHOOTING_RANGE 1920
#define PERCEPTION_RANGE 200
#define RIGHT 1
#define LEFT 2

Character::Character(int pos_x,
                     int pos_y,
                     int collision_range) : life(CHARACTER_LIFE),
                                            dead(false),
                                            pos_x(pos_x),
                                            pos_y(pos_y),
                                            moving_x(0),
                                            moving_y(0),
                                            target(nullptr),
                                            collision_range(collision_range),
                                            orientation(RIGHT) {}

void Character::move(int move_x, int move_y) {
    pos_x += move_x;
    pos_y += move_y;
    if (move_x > 0) {
        orientation = RIGHT;
    } else {
        orientation = LEFT;
    }
}

bool Character::collision(Character *other, int move_x, int move_y) const {
    auto distance = Character::distance(other, pos_x + move_x, pos_y + move_y);
    return distance < this->collision_range + other->collision_range;
}

void Character::update_move() {
    int distance_x = this->pos_x - target->pos_x;
    int distance_y = this->pos_y - target->pos_y;
    double distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
    double dir_x = distance_x / distance;
    double dir_y = distance_y / distance;
    lround(dir_x);
    lround(dir_y);
    moving_x = (int)dir_x;
    moving_y = (int)dir_y;
}

void Character::interact() {
    // need to verify the life of the target
    if (target && target_collision()) {
        target->life -= DEFAULT_DAMAGE;
        return;
    }
    pos_x += moving_x;
    pos_y += moving_y;
}

void Character::shoot(std::map<int, Character*>& enemies) {
    Character *enemy;
    if (orientation == RIGHT) {
        enemy = find_enemies_right(enemies);
    } else {
        enemy = find_enemies_left(enemies);
    }
    if (enemy && enemy->life > 0) {
        enemy->life -= DEFAULT_DAMAGE;
    }
}

bool Character::is_dead() const {
    return dead;
}

void Character::check_target(Character *other) {
    if (other == target) {
        update_move();
        return;
    }
    if ((!target || target->dead) && distance_from(other) < PERCEPTION_RANGE) {
        target = other;
        update_move();
    }
}

int Character::get_pos_x() const {
    return pos_x;
}

int Character::get_pos_y() const {
    return pos_y;
}

double Character::distance(Character *other, int new_pos_x, int new_pos_y) {
    int distance_x = other->pos_x - new_pos_x;
    int distance_y = other->pos_y - new_pos_y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

double Character::distance_from(Character *other) const {
    int distance_x = this->pos_x - other->pos_x;
    int distance_y = this->pos_y - other->pos_y;
    return sqrt((distance_x * distance_x) + (distance_y * distance_y));
}

bool Character::target_collision() {
    int distance_x = this->pos_x - target->pos_x;
    int distance_y = this->pos_y - target->pos_y;
    double distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
    return distance < this->collision_range + target->collision_range;
}

Character *Character::find_enemies_left(std::map<int, Character *> &enemies) const {
    int closest_zombie_pos = -1;
    Character *closest_zombie = nullptr;
    for (auto character : enemies) {
        auto *enemy = character.second;
        if (enemy->pos_x < this->pos_x &&
        this->pos_y < (enemy->pos_y + enemy->collision_range) &&
        this->pos_y > (enemy->pos_y - enemy->collision_range) &&
        enemy->pos_x > closest_zombie_pos) {
            closest_zombie_pos = enemy->pos_x;
            closest_zombie = enemy;
        }
    }
    return closest_zombie;
}

Character *Character::find_enemies_right(std::map<int, Character *> &enemies) const {
    int closest_zombie_pos = MAX_SHOOTING_RANGE;
    Character *closest_zombie = nullptr;
    for (auto character : enemies) {
        auto *enemy = character.second;
        if (enemy->pos_x > this->pos_x &&
            this->pos_y < (enemy->pos_y + enemy->collision_range) &&
            this->pos_y > (enemy->pos_y - enemy->collision_range) &&
            enemy->pos_x < closest_zombie_pos) {
            closest_zombie_pos = enemy->pos_x;
            closest_zombie = enemy;
        }
    }
    return closest_zombie;
}
