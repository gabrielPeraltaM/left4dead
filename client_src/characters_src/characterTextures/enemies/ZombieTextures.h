//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_ZOMBIETEXTURES_H
#define LEFT4DEAD_ZOMBIETEXTURES_H

#include "EnemyTexture.h"

struct ZombieTextures : EnemyTexture {
    ZombieTextures(Renderer &renderer) : EnemyTexture(renderer, RESOURCE_PATH "/Zombie/") {
        frameHeight = 96;
        frameWidth = 96;
        borderLeft = 32;
        borderTop = 30;
        width = 30;
        height = 70;
    }
};

#endif //LEFT4DEAD_ZOMBIETEXTURES_H
