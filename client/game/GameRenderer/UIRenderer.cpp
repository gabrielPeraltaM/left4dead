//
// Created by ignacio on 6/10/23.
//

#include "UIRenderer.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#define GAPX (SCREEN_WIDTH * 0.05)
#define GAPY (SCREEN_HEIGHT * 0.05)
#define HEIGHT (SCREEN_HEIGHT * 0.03)
#define SIZE_FACTOR 2
#define AMMO_FACTOR 10
#define ALPHA 100

UIRenderer::UIRenderer(Renderer &renderer) : renderer(renderer) {}

void UIRenderer::render() {
  renderHealthBar();
  renderAmmo();
}

void UIRenderer::setPlayer(Character *thisPlayer) {
  player = thisPlayer;
  maxHealth = player->getMaxHealth();
  maxAmmo = player->getMaxAmmo();
}

void UIRenderer::renderHealthBar() {
  // Render a red rectangle representing the health at top left corner
  renderer.SetDrawColor(255, 0, 0, ALPHA);
  renderer.FillRect(Rect(GAPX, GAPY, player->getHealth() * SIZE_FACTOR, HEIGHT));
  // Render a black border around the health bar
  renderer.SetDrawColor(0, 0, 0, ALPHA);
  renderer.DrawRect(Rect(GAPX, GAPY, maxHealth * SIZE_FACTOR, HEIGHT));
}

void UIRenderer::renderAmmo() {
  // Render a blue rectangle representing the ammo at top left corner
  renderer.SetDrawColor(0, 0, 255, ALPHA);
  renderer.FillRect(Rect(GAPX, GAPY * SIZE_FACTOR, player->getAmmo() * SIZE_FACTOR * AMMO_FACTOR, HEIGHT));
  // Render a black border around the ammo bar
  renderer.SetDrawColor(0, 0, 0, ALPHA);
  renderer.DrawRect(Rect(GAPX, GAPY * SIZE_FACTOR, maxAmmo * SIZE_FACTOR * AMMO_FACTOR, HEIGHT));
}
