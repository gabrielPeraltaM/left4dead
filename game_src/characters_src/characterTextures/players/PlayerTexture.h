//
// Created by ignacio on 5/28/23.
//

#ifndef LEFT4DEAD_PLAYERTEXTURE_H
#define LEFT4DEAD_PLAYERTEXTURE_H

#include "game_src/characters_src/characterTextures/CharacterTexture.h"
struct PlayerTexture : public CharacterTexture {
  Texture *shoot;
  Texture *reload;
  PlayerTexture(Renderer &renderer, const char *srcPath) : CharacterTexture(renderer, srcPath) {
    attack = new Texture(renderer, srcPath + std::string("Attack.png"));
    shoot = new Texture(renderer, srcPath + std::string("Shot_1.png"));
    reload = new Texture(renderer, srcPath + std::string("Recharge.png"));
    borderLeft = 46;
    width = 33;
    borderTop = 60;
    height = 70;
  }
  PlayerTexture() = default;
};

#endif  // LEFT4DEAD_PLAYERTEXTURE_H
