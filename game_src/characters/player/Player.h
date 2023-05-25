//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H

#include <string>

#include "../Character.h"

class Player : public Character {
private:
    int maxAmmo;
    int ammo = maxAmmo;
    int burst;
public:
    Player(int burst, int maxAmmo, const char *srcPath, int16_t posX, int16_t posY,
           int16_t damage, int16_t attackSpeed, int16_t attackRange);

    void attack() override;

    void die() override;

    void spawn() override;

    void update() override;

    void destroy() override;

    void reload();

    void shoot();
};

#endif  // LEFT4DEAD_PLAYER_H
