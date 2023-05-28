//
// Created by ignacio on 5/28/23.
//

#ifndef LEFT4DEAD_ENEMYTEXTURE_H
#define LEFT4DEAD_ENEMYTEXTURE_H

#include "game_src/characters_src/characterTextures/CharacterTexture.h"
struct EnemyTexture : public CharacterTexture {
  EnemyTexture(Renderer &renderer, const char *srcPath) : CharacterTexture(renderer, srcPath) {
    attack = new Texture(renderer, srcPath + std::string("Attack_1.png"));
    borderLeft = 46;
    width = 33;
    borderTop = 60;
    height = 70;
  }
  EnemyTexture() = default;
};

#endif  // LEFT4DEAD_ENEMYTEXTURE_H
