//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_SPEAR_H
#define LEFT4DEAD_SPEAR_H

#include "Enemy.h"
class Spear : public Enemy {
 private:
 public:
  Spear(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
};

#endif  // LEFT4DEAD_SPEAR_H
