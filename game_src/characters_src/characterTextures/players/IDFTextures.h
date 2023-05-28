//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_IDFTEXTURES_H
#define LEFT4DEAD_IDFTEXTURES_H

#include "PlayerTexture.h"

struct IDFTextures : PlayerTexture {
    IDFTextures(Renderer &renderer) : PlayerTexture(renderer, RESOURCE_PATH "/IDF/") {
        borderLeft= 46;
        width = 33;
        borderTop = 60;
        height = 70;
    }
};

#endif //LEFT4DEAD_IDFTEXTURES_H
