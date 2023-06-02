//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_VENOM_H
#define LEFT4DEAD_VENOM_H

#include "Enemy.h"
class Venom : public Enemy {
  private:
  public:
  Venom(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
};

#endif  // LEFT4DEAD_VENOM_H
