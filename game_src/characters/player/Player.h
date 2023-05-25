//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H

#include <string>

#include "../Character.h"

class Player : public Character {
 private:
 public:
  Player();
  void attack() override;
  void die() override;
  void spawn() override;
  void update() override;
  void destroy() override;
  void getCharacterType() override;
};

#endif  // LEFT4DEAD_PLAYER_H
