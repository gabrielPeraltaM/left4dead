//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_P90TEXTURES_H
#define LEFT4DEAD_P90TEXTURES_H

#include "PlayerTexture.h"

struct P90Textures : public PlayerTexture {
  P90Textures(Renderer &renderer) : PlayerTexture(renderer, RESOURCE_PATH "/P90/") {
      borderLeft= 46;
      width = 33;
      borderTop = 60;
      height = 70;
}
};

#endif  // LEFT4DEAD_P90TEXTURES_H
