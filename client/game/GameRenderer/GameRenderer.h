//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_PRUEBA_GAMERENDERER_H
#define SDL_PRUEBA_GAMERENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "BackgroundRenderer.h"
#include "PlayerRenderer.h"
#include "UIRenderer.h"
#include "client/characters/Character.h"
#include "common_src/thread.h"
#include "../../StateQueue.h"

#define CHARACTER_ATTRIBUTES_AMOUNT 7

using namespace SDL2pp;

class GameRenderer : public Thread {
 private:
  Renderer &renderer;
  bool &running;
  std::map<int, std::shared_ptr<Character>> characters;
  const int playerId;
  const int mapSelected;
  bool &isLoadingPlayers;
  uint8_t &gameStatus;
  int numCharacters;
  std::vector<uint16_t> state = std::vector<uint16_t>(numCharacters * CHARACTER_ATTRIBUTES_AMOUNT);
  StateQueue &states;
  BackgroundRenderer backgroundRenderer =
      BackgroundRenderer(renderer, characters, playerId, mapSelected, gameStatus);
  UIRenderer uiRenderer = UIRenderer(renderer);
  PlayerRenderer playerRenderer = PlayerRenderer(characters, renderer);

 public:
  GameRenderer(Renderer &renderer, bool &running,
               int playerId, int mapSelected, bool &isLoadingPlayers, uint8_t &gameStatus, StateQueue &states, int numCharacters);

  void run() override;

  void initialize_characters();

  void update_characters();
};

#endif  // SDL_PRUEBA_GAMERENDERER_H
