//
// Created by ignacio on 5/28/23.
//

#include "GameStorage.h"

#include "client_src/characters_src/characterData/enemies/ZombieData.h"
#include "client_src/characters_src/characterData/players/IDFData.h"
#include "client_src/characters_src/characterData/players/P90Data.h"
#include "client_src/characters_src/characterTextures/enemies/ZombieTextures.h"
#include "client_src/characters_src/characterTextures/players/IDFTextures.h"
#include "client_src/characters_src/characterTextures/players/P90Textures.h"

void GameStorage::addPlayer(int16_t x, int16_t y, int playerId) {
  Player player(x, y, playerId, data["IDF"], playerTextures["IDF"]);
  players.emplace_back(player);
}

void GameStorage::addZombie(int16_t x, int16_t y) {
  Enemy zombie(x, y, data["Zombie"], enemyTextures["Zombie"]);
  enemies.emplace_back(zombie);
}
std::vector<Player>& GameStorage::getPlayers() {
  return players;
}

std::list<Enemy>& GameStorage::getEnemies() {
  return enemies;
}

std::unordered_map<std::string, PlayerTexture>& GameStorage::getPlayerTextures() {
  return playerTextures;
}

std::unordered_map<std::string, EnemyTexture>& GameStorage::getEnemyTextures() {
  return enemyTextures;
}

std::unordered_map<std::string, CharacterData>& GameStorage::getData() {
  return data;
}
GameStorage::GameStorage(Renderer &renderer) : renderer(renderer) {
  loadTextures();
  loadData();
  addPlayer(200, 800, 0);
  addPlayer(600, 800, 1);
  addZombie(300, 800);
}
void GameStorage::loadData() {
  IDFData idfData;
  data.emplace("IDF", idfData);

  P90Data p90Data;
  data.emplace("P90", p90Data);
  //  Add the rest of the players

  // Load the zombies data
  ZombieData zombieData;
  data.emplace("Zombie", zombieData);
}

void GameStorage::loadTextures() {
  IDFTextures idf(renderer);
  playerTextures.emplace("IDF", idf);

  // P90
  P90Textures p90(renderer);
  playerTextures.emplace("P90", p90);
  // Add the rest of the players

  // Load the zombies textures
  ZombieTextures zombie(renderer);
  enemyTextures.emplace("Zombie", zombie);
}
