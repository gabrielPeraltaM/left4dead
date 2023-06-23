//
// Created by ignacio on 6/19/23.
//

#ifndef LEFT4DEAD_GAMEMONITOR_H
#define LEFT4DEAD_GAMEMONITOR_H

#include <mutex>
#include <vector>

#include "client/characters/Character.h"

class GameMonitor {
 private:
  std::mutex mutex;
  std::map<int, Character> characters;
 public:
  GameMonitor() = default;
  void addCharacter(int playerId, const char* type, int x, int y);
  void addCharacter(int playerId, const char* type, int x, int y, int frameSize);
  void getCharacterPosition(int playerId, int* x, int* y);
  void setCameraX(int playerId, int x);
  void setCameraY(int playerId, int y);
  void attack(int playerId);
  void move(int playerId, int x, int y);
  void shoot(int playerId);
  void reload(int playerId);
  void hurt(int playerId);
  void die(int playerId);
  void kill(int playerId);
  void idle(int playerId);
  bool isDead(int playerId);
  int getFrameSize(int playerId);
  bool getFlip(int playerId);
  std::string getCharacterType(int playerId);
  std::string getCharacterAction(int playerId);
  unsigned long getCharactersAmount();
};

#endif  // LEFT4DEAD_GAMEMONITOR_H
