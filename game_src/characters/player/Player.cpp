//
// Created by ignacio on 5/24/23.
//

#include "Player.h"

void Player::attack() {
    if (ammo > 0) {
        ammo--;
        shoot();
    } else {
        reload();
    }
}

void Player::die() {}

void Player::spawn() {}

void Player::update() {}

void Player::destroy() {}

void Player::reload() {
    ammo = maxAmmo;
}

Player::Player(int burst, int maxAmmo, const char *srcPath, int16_t posX, int16_t posY,
               int16_t damage, int16_t attackSpeed, int16_t attackRange) : Character(100, 10, damage, attackSpeed,
                                                                                     attackRange, 40,
                                                                                     100, srcPath, 30, 60),
                                                                           burst(burst), maxAmmo(maxAmmo) {}

void Player::shoot() {

}
