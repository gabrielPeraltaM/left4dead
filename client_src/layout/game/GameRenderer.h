//
// Created by ignacio on 6/2/23.
//

#ifndef LEFT4DEAD_GAMERENDERER_H
#define LEFT4DEAD_GAMERENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "GameStorage.h"

using namespace SDL2pp;

class GameRenderer {
 private:
  Renderer &renderer;
  int width;
  int height;
  std::string background_src;
  Texture background = Texture(renderer, background_src);
  int mapScrollingOffset = 0;
  GameStorage &gameStorage;
  int playerId;
 public:
  GameRenderer(Renderer &renderer, int width, int height,
               std::string &background_src, GameStorage &gameStorage, int playerId);
  void setSize(int width, int height);
  void render();
  void renderInterface();
  void renderBackground();
  void renderPlayers();
  void renderEnemies();
  void getMapOffset();
  ~GameRenderer() = default;
};

#endif  // LEFT4DEAD_GAMERENDERER_H
