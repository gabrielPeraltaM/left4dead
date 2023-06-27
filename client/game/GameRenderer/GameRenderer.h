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

using namespace SDL2pp;

class GameRenderer : public Thread {
 private:
  Renderer &renderer;
  bool &running;
  std::map<int, std::shared_ptr<Character>> &characters;
  const int playerId;
  const int mapSelected;
  bool &isLoadingPlayers;
  BackgroundRenderer backgroundRenderer =
      BackgroundRenderer(renderer, characters, playerId, mapSelected);
  UIRenderer uiRenderer = UIRenderer(renderer);
  PlayerRenderer playerRenderer = PlayerRenderer(characters, renderer);

 public:
  GameRenderer(Renderer &renderer, bool &running,
               std::map<int, std::shared_ptr<Character>> &characters,
               int playerId, int mapSelected, bool &isLoadingPlayers);

  void run() override;
};

#endif  // SDL_PRUEBA_GAMERENDERER_H
