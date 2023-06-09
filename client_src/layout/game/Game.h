//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <list>

#include "GameProtocol.h"
#include "GameRenderer.h"
#include "GameStorage.h"
#include "Receiver.h"
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
  int width;
  int height;

  int playerId;

  const int difficulty = 2;  // 1 = easy, 2 = medium, 3 = hard

  // Game storage
  GameStorage gameStorage = GameStorage(renderer);

  Protocol &protocol;

  // Game functions
  GameProtocol gameProtocol = GameProtocol(protocol, was_closed);

  // Protocol
  uint32_t gameId;
  bool &was_closed;
  Receiver receiver = Receiver(&protocol, was_closed, gameStorage.getPlayers());

  // Components
  std::string background_src;
  GameRenderer gameRenderer = GameRenderer(renderer, width, height, background_src, gameStorage, playerId);

 public:
  Game(int difficulty, std::string &background_src, Protocol &protocol,
       uint32_t gameId, int playerId, bool &was_closed);
  ~Game();
  void StartGame();
};

#endif  // LEFT4DEAD_GAME_H
