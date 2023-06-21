//
// Created by gabriel on 13/06/23.
//

#include "Survivor.h"

#define SURVIVOR_LIFE 100
#define DEFAULT_DAMAGE 1
#define DEFAULT_ATTACK_DAMAGE 4
#define MAX_SHOOTING_RANGE 1920
#define RIGHT 1
#define LEFT 2
#define SURVIVOR_COLLISION_RANGE 22
#define DEFAULT_SURVIVOR_AMMO 100

#define RELOAD_DELAY 40
#define ATTACK_DELAY 10

Survivor::Survivor(int pos_x, int pos_y) : Character(SURVIVOR_LIFE, pos_x, pos_y,
                                                     SURVIVOR_COLLISION_RANGE,
                                                     DEFAULT_SURVIVOR_AMMO),
                                           orientation(RIGHT),
                                           delay(0) {}

void Survivor::move(int move_x, int move_y) {
    if (state != NOT) {
        return;
    }
    pos_x += move_x;
    pos_y += move_y;
    if (move_x > 0) {
        orientation = RIGHT;
    } else {
        orientation = LEFT;
    }
}

bool Survivor::collision(Character *other, int pos_x, int pos_y) {
    auto distance = Character::distance(other, pos_x, pos_y);
    return distance < this->collision_range + other->get_collision_range();
}

void Survivor::shoot(std::map<int, Character*>& enemies) {
    if ((state != NOT && state != SHOOTING) || ammo == 0) {
        return;
    }
    this->start_shooting();
    Character *enemy;
    --ammo;
    if (orientation == RIGHT) {
        enemy = find_enemies_right(enemies);
    } else {
        enemy = find_enemies_left(enemies);
    }
    if (enemy) {
        enemy->receive_damage(DEFAULT_DAMAGE);
    }
}

void Survivor::reload() {
    if (state == DEAD ||
        state == DAMAGING ||
        state == ATTACKING ||
        ammo == DEFAULT_SURVIVOR_AMMO) {
        return;
    }
    if (delay < RELOAD_DELAY) {
        ++delay;
        state = RELOADING;
        return;
    }
    delay = 0;
    ammo = DEFAULT_SURVIVOR_AMMO;
    state = NOT;
}

void Survivor::attack(std::map<int, Character*>& enemies) {
    if (state == DEAD || state == RELOADING) {
        return;
    }
    /*if (delay < ATTACK_DELAY) {
        ++delay;
        state = ATTACKING;
        return;
    }*/
    state = ATTACKING;
    for (auto character : enemies) {
        auto *enemy = character.second;
        if ((orientation == RIGHT &&
            enemy->get_pos_x() > pos_x &&
            collision(enemy, pos_x, pos_y)) ||
            (orientation == LEFT &&
            enemy->get_pos_x() < pos_x &&
            collision(enemy, pos_x, pos_y))) {
            enemy->receive_damage(DEFAULT_ATTACK_DAMAGE);
        }
    }
}

void Survivor::receive_damage(int damage) {
    if (state == DEAD) {
        return;
    }
    life -= damage;
    //state = DAMAGING;
    if (life <= 0) {
        life = 0;
        state = DEAD;
        collision_range = 2;
    }
}

void Survivor::reset_state() {
    if (state != SHOOTING && state != ATTACKING) {
        return;
    }
    if (state == ATTACKING && delay < ATTACK_DELAY) {
        ++delay;
        return;
    }
    delay = 0;
    state = NOT;
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
