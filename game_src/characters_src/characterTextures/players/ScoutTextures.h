//
// Created by ignacio on 5/28/23.
//

#ifndef LEFT4DEAD_SCOUTTEXTURES_H
#define LEFT4DEAD_SCOUTTEXTURES_H

#include "PlayerTexture.h"
class ScoutTextures : public PlayerTexture {
 public:
  ScoutTextures(Renderer &renderer) : PlayerTexture(renderer, RESOURCE_PATH "/Scout/") {
    borderLeft = 46;
    width = 33;
    borderTop = 60;
    height = 70;
  }
}

#endif  // LEFT4DEAD_SCOUTTEXTURES_H
