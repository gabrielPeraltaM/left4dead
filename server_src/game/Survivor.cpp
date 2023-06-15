//
// Created by gabriel on 13/06/23.
//

#include "Survivor.h"

#define SURVIVOR_LIFE 100
#define DEFAULT_DAMAGE 1
#define MAX_SHOOTING_RANGE 1920
#define RIGHT 1
#define LEFT 2
#define SURVIVOR_COLLISION_RANGE 22

Survivor::Survivor(int pos_x, int pos_y) : Character(pos_x, pos_y, SURVIVOR_COLLISION_RANGE),
                                           life(SURVIVOR_LIFE),
                                           orientation(RIGHT) {}

void Survivor::move(int move_x, int move_y) {
    pos_x += move_x;
    pos_y += move_y;
    if (move_x > 0) {
        orientation = RIGHT;
    } else {
        orientation = LEFT;
    }
}

bool Survivor::collision(Character *other, int move_x, int move_y) {
    auto distance = Character::distance(other, pos_x + move_x, pos_y + move_y);
    return distance < this->collision_range + other->get_collision_range();
}

void Survivor::shoot(std::map<int, Character*>& enemies) {
    this->star_shooting();
    Character *enemy;
    if (orientation == RIGHT) {
        enemy = find_enemies_right(enemies);
    } else {
        enemy = find_enemies_left(enemies);
    }
    if (enemy) {
        enemy->receive_damage(DEFAULT_DAMAGE);
    }
}

void Survivor::receive_damage(int damage) {
    if (dead) {
        return;
    }
    life -= damage;
    if (life <= 0) {
        dead = true;
    }
}

Character *Survivor::find_enemies_left(std::map<int, Character *> &enemies) const {
    int closest_zombie_pos = -1;
    Character *closest_zombie = nullptr;
    for (auto character : enemies) {
        auto *enemy = character.second;
        if (enemy->get_pos_x() < this->pos_x &&
            this->pos_y < (enemy->get_pos_y() + enemy->get_collision_range()) &&
            this->pos_y > (enemy->get_pos_y() - enemy->get_collision_range()) &&
            enemy->get_pos_x() > closest_zombie_pos) {
            closest_zombie_pos = enemy->get_pos_x();
            closest_zombie = enemy;
        }
    }
    return closest_zombie;
}

Character *Survivor::find_enemies_right(std::map<int, Character *> &enemies) const {
    int closest_zombie_pos = MAX_SHOOTING_RANGE;
    Character *closest_zombie = nullptr;
    for (auto character : enemies) {
        auto *enemy = character.second;
        if (enemy->get_pos_x() > this->pos_x &&
            this->pos_y < (enemy->get_pos_y() + enemy->get_collision_range()) &&
                          this->pos_y > (enemy->get_pos_y() - enemy->get_collision_range()) &&
            enemy->get_pos_x() < closest_zombie_pos) {
            closest_zombie_pos = enemy->get_pos_x();
            closest_zombie = enemy;
        }
    }
    return closest_zombie;
}

void Survivor::interact() {
}

void Survivor::check_target(Character *other) {
}
