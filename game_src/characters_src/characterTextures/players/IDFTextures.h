//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_IDFTEXTURES_H
#define LEFT4DEAD_IDFTEXTURES_H

#include "game_src/characters_src/characterTextures/CharacterTexture.h"

struct IDFTextures : CharacterTexture {
    IDFTextures(Renderer &renderer) : CharacterTexture(renderer, RESOURCE_PATH "/IDF/") {
        attack = new Texture(renderer, RESOURCE_PATH "/IDF/Attack.png");
    }
};

#endif //LEFT4DEAD_IDFTEXTURES_H
