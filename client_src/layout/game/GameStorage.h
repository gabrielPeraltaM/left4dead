//
// Created by ignacio on 5/28/23.
//

#ifndef LEFT4DEAD_GAMESTORAGE_H
#define LEFT4DEAD_GAMESTORAGE_H

#include <list>
#include <string>
#include <vector>

#include "client_src/characters_src/character/enemies/Enemy.h"
#include "client_src/characters_src/character/players/Player.h"
#include "client_src/characters_src/characterTextures/enemies/EnemyTexture.h"
// Aca se va a guardar los sprites, sonidos, etc
class GameStorage {
 private:
  std::vector<Player> players;
  std::list<Enemy> enemies;
  std::unordered_map<std::string, PlayerTexture> playerTextures;
  std::unordered_map<std::string, EnemyTexture>
      enemyTextures;  // Los strings van a ser enums
  std::unordered_map<std::string, CharacterData> data;
  Renderer &renderer;
 public:
  GameStorage(Renderer &renderer);
  ~GameStorage() = default;
  void addPlayer(int16_t x, int16_t y, int playerId);
  void addZombie(int16_t x, int16_t y);
  void loadTextures();
  void loadData();
  std::vector<Player> &getPlayers();
  std::list<Enemy> &getEnemies();
  std::unordered_map<std::string, PlayerTexture> &getPlayerTextures();
  std::unordered_map<std::string, EnemyTexture> &getEnemyTextures();
  std::unordered_map<std::string, CharacterData> &getData();
};

#endif  // LEFT4DEAD_GAMESTORAGE_H
