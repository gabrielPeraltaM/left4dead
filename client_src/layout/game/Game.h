//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <list>

#include "Receiver.h"
#include "client_src/characters_src/character/enemies/Enemy.h"
#include "client_src/characters_src/character/players/Player.h"
#include "client_src/characters_src/characterData/CharacterData.h"
#include "client_src/characters_src/characterTextures/CharacterTexture.h"
#include "client_src/characters_src/characterTextures/enemies/EnemyTexture.h"
#include "client_src/characters_src/characterTextures/players/PlayerTexture.h"
#include "client_src/client/Protocol.h"
#include "common_src/protocol.h"
using namespace SDL2pp;

class Game {
 private:
  // SDL variables
  SDL_DisplayMode DM = SDL_DisplayMode();
  Window window =
      Window("Left4Dead", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800,
             600, SDL_WINDOW_MAXIMIZED);
  Renderer renderer = Renderer(window, -1, SDL_RENDERER_ACCELERATED);
  int width = 800;
  int height = 600;

  // Background
  Texture *background = nullptr;
  int mapScrollingOffset = 0;
  int enemyScrollingOffset = 0;

  // Initialization
  void loadData();
  void loadBackground(std::string &background_src);

  const int difficulty = 1;  // 1 = easy, 2 = medium, 3 = hard

  // Game storage
  std::vector<Player> players;
  std::list<Enemy> enemies;
  std::unordered_map<std::string, PlayerTexture> playerTextures;
  std::unordered_map<std::string, EnemyTexture>
      enemyTextures;  // Los strings van a ser enums
  std::unordered_map<std::string, CharacterData> data;

  // Game functions
  void addPlayer(int16_t x, int16_t y, int playerId);
  void addZombie(int16_t x, int16_t y);
  void spawnZombie();
  void drawBackground();
  void drawZombies();
  void drawOtherPlayers();
  void drawPlayer(Player &player);
  void playerAction(Player &player);
  void loadTextures();

  // Protocol
  Protocol &protocol;
  uint32_t gameId;
  int playerId;
  bool &was_closed;
  Receiver receiver = Receiver(&protocol, was_closed, players);

 public:
  Game(int difficulty, std::string &background_src, Protocol &protocol,
       uint32_t gameId, int playerId, bool &was_closed);
  ~Game();
  void StartGame();
};

#endif  // LEFT4DEAD_GAME_H
