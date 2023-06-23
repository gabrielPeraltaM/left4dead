//
// Created by ignacio on 6/19/23.
//

#include "GameMonitor.h"
/*
 * Character(int posX, int posY, int id, const char* type);
 */

void GameMonitor::addCharacter(int playerId, const char *type, int x, int y) {
  std::lock_guard<std::mutex> lock(mutex);
  characters.emplace(playerId, Character(x, y, playerId, type));
}

void GameMonitor::addCharacter(int playerId, const char *type, int x, int y,
                               int frameSize) {
  std::lock_guard<std::mutex> lock(mutex);
  characters.emplace(playerId, Character(x, y, playerId, type, frameSize));
}

void GameMonitor::attack(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.attack();
}

void GameMonitor::move(int playerId, int x, int y) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.move(x, y);
}

void GameMonitor::shoot(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.shoot();
}

void GameMonitor::reload(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.reload();
}

void GameMonitor::hurt(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.hurt();
}

void GameMonitor::die(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.die();
}

unsigned long GameMonitor::getCharactersAmount() {
  std::lock_guard<std::mutex> lock(mutex);
  return characters.size();
}

void GameMonitor::setCameraX(int playerId, int x) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.setCameraX(x);
}

void GameMonitor::setCameraY(int playerId, int y) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.setCameraY(y);
}

void GameMonitor::getCharacterPosition(int playerId, int *x, int *y) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.getPosition(x, y);
}

int GameMonitor::getFrameSize(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  return player.getFrameSize();
}

std::string GameMonitor::getCharacterType(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  return player.getType();
}

std::string GameMonitor::getCharacterAction(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  return player.getAction();
}

void GameMonitor::kill(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.kill();
}

void GameMonitor::idle(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  player.idle();
}
bool GameMonitor::isDead(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  return player.isDead();
}
bool GameMonitor::getFlip(int playerId) {
  std::lock_guard<std::mutex> lock(mutex);
  Character &player = characters.at(playerId);
  return player.getFlip();
}
