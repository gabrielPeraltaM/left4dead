//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_JUMPER_H
#define LEFT4DEAD_JUMPER_H

#include "Enemy.h"
class Jumper : public Enemy {
 private:
 public:
  Jumper(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
};

#endif  // LEFT4DEAD_JUMPER_H
