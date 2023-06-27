//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_UIRENDERER_H
#define SDL_PRUEBA_UIRENDERER_H

#include <SDL2pp/SDL2pp.hh>

#include "client/characters/Character.h"
using namespace SDL2pp;

class UIRenderer {
 private:
  Renderer &renderer;
  Character *player = nullptr;
  int maxHealth = 100;
  int maxAmmo = 100;
  void renderHealthBar();
  void renderAmmo();
 public:
  explicit UIRenderer(Renderer &renderer);
  void setPlayer(Character *player);
  void render();
};

#endif  // SDL_PRUEBA_UIRENDERER_H
