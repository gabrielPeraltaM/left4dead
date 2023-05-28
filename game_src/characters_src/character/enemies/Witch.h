//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_WITCH_H
#define LEFT4DEAD_WITCH_H

#include "Enemy.h"
class Witch : public Enemy {
 private:
 public:
  Witch(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
};

#endif  // LEFT4DEAD_WITCH_H
