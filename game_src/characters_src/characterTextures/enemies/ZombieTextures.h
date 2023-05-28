//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_ZOMBIETEXTURES_H
#define LEFT4DEAD_ZOMBIETEXTURES_H

#include "game_src/characters_src/characterTextures/CharacterTexture.h"

struct ZombieTextures : CharacterTexture {
    ZombieTextures(Renderer &renderer) : CharacterTexture(renderer, RESOURCE_PATH "/Zombie/") {
        attack = new Texture(renderer, RESOURCE_PATH "/Zombie/Attack_1.png");
    }
};

#endif //LEFT4DEAD_ZOMBIETEXTURES_H
