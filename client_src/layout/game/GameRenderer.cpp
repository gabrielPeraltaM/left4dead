//
// Created by ignacio on 6/2/23.
//

#include "GameRenderer.h"

GameRenderer::GameRenderer(Renderer& renderer, int width, int height,
                           std::string& background_src,
                           GameStorage& gameStorage, int playerId)
    : renderer(renderer),
      width(width),
      height(height),
      background_src(background_src),
      gameStorage(gameStorage),
      playerId(playerId) {}

void GameRenderer::render() {
  getMapOffset();
  renderBackground();
  renderPlayers();
  renderEnemies();
  renderInterface();
}

void GameRenderer::renderInterface() {
  int gapX = width * 0.05;
  int gapY = height * 0.05;
  Uint8 alpha = 100;
  int frameWidth = 100 * (width / 800);
  int frameHeight = 8 * (height / 300);

  // Render a red rectangle representing the health at top left corner
  renderer.SetDrawColor(255, 0, 0, alpha);
  renderer.FillRect(Rect(gapX, gapY, frameWidth, frameHeight));
  // Render a black border around the health bar
  renderer.SetDrawColor(0, 0, 0, alpha);
  renderer.DrawRect(Rect(gapX, gapY, frameWidth, frameHeight));

  // Render a blue rectangle representing the stamina below the health bar
  renderer.SetDrawColor(0, 0, 255, alpha);
  renderer.FillRect(Rect(gapX, gapY + 2 * frameHeight, frameWidth, frameHeight));
  // Render a black border around the stamina bar
  renderer.SetDrawColor(0, 0, 0, alpha);
  renderer.DrawRect(Rect(gapX, gapY + 2 * frameHeight, frameWidth, frameHeight));

  // Render a green rectangle representing the ammo below the stamina bar
  renderer.SetDrawColor(0, 255, 0, alpha);
  renderer.FillRect(Rect(gapX, gapY + 4 * frameHeight, frameWidth, frameHeight));
  // Render a black border around the ammo bar
  renderer.SetDrawColor(0, 0, 0, alpha);
  renderer.DrawRect(Rect(gapX, gapY + 4 * frameHeight, frameWidth, frameHeight));
}
void GameRenderer::renderBackground() {
  Rect srcRect = Rect(0, 0, width, height);
  Rect dstRect = Rect(-mapScrollingOffset, 0, width, height);

  // Draw the background
  renderer.Copy(background, srcRect, dstRect);

  // Draw the background again to simulate parallax
  dstRect.SetX(width - mapScrollingOffset);
  renderer.Copy(background, srcRect, dstRect);
}

void GameRenderer::renderPlayers() {
  for (auto& player : gameStorage.getPlayers()) {
    Texture* sprite = player.getCurrentSprite();
    Rect srcrect(player.getFrameWidth() * player.getAnimationFrame(), 0,
                 player.getFrameWidth(), player.getFrameHeight());
    int x = player.getPosX();
    int y = player.getPosY();

    Rect dstrect(x, y, player.getFrameWidth(), player.getFrameHeight());
    SDL_RenderCopyEx(renderer.Get(), sprite->Get(), &srcrect, &dstrect, 0,
                     nullptr, player.getFlip());
  }
}

void GameRenderer::renderEnemies() {
  for (auto& enemy : gameStorage.getEnemies()) {
    Texture* sprite = enemy.getCurrentSprite();
    Rect srcrect(enemy.getFrameWidth() * enemy.getAnimationFrame(), 0,
                 enemy.getFrameWidth(), enemy.getFrameHeight());
    int x = enemy.getPosX();
    int y = enemy.getPosY();
    Rect dstrect(x, y, enemy.getFrameWidth(), enemy.getFrameHeight());
    SDL_RenderCopyEx(renderer.Get(), sprite->Get(), &srcrect, &dstrect, 0,
                     nullptr, enemy.getFlip());
  }
}
void GameRenderer::setSize(int newWidth, int newHeight) {
  width = newWidth;
  height = newHeight;
}
void GameRenderer::getMapOffset() {
  return ;
  std::cout << "playerID: " << playerId << "\n";
  Player& player = gameStorage.getPlayers()[playerId];
  int playerX = player.getPosX();
  return ;
  if (playerX < 0.01 * width) {
    mapScrollingOffset = 0.1 * width - playerX;
  }
}
