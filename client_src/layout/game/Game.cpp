//
// Created by ignacio on 5/24/23.
//

#include "Game.h"

#include <cstdio>

#include "client_src/characters_src/character/enemies/Zombie.h"
#include "client_src/characters_src/characterData/enemies/ZombieData.h"
#include "client_src/characters_src/characterData/players/IDFData.h"
#include "client_src/characters_src/characterData/players/P90Data.h"
#include "client_src/characters_src/characterTextures/enemies/ZombieTextures.h"
#include "client_src/characters_src/characterTextures/players/IDFTextures.h"
#include "client_src/characters_src/characterTextures/players/P90Textures.h"

void Game::StartGame() {
  // Initialize SDL
  SDL sdl = SDL(SDL_INIT_VIDEO);
  // Get the screen size
  SDL_GetCurrentDisplayMode(0, &DM);
  width = DM.w;
  height = DM.h;

  // Add the initial zombies
  spawnZombie();
  addPlayer(200, 800, playerId);

  // Game loop
  SDL_Event event;
  bool running = true;
  while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      // Exit game
      if (event.type == SDL_QUIT) {
        running = false;
        break;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
          case SDLK_q:
            running = false;
        }
      }
    }

    playerAction(players[playerId]);
    // Clear screen
    renderer.Clear();

    // Draw the background
    drawBackground();

    // Draw the characters
    drawOtherPlayers();
    drawZombies();

    renderer.Present();
    SDL_Delay(1000 / 60);
  }
}

void Game::drawOtherPlayers() {
  for (auto &player : players) {
    Texture *sprite = player.getCurrentSprite();
    player.scrollRight(enemyScrollingOffset);
    Rect srcrect(player.getFrameWidth() * player.getAnimationFrame(), 0,
                 player.getFrameWidth(), player.getFrameHeight());

    // Check if the player is in the border
    int x = player.getPosX();
    int y = player.getPosY();

    Rect dstrect(x, y, player.getFrameWidth(), player.getFrameHeight());
    SDL_RenderCopyEx(renderer.Get(), sprite->Get(), &srcrect, &dstrect, 0,
                     nullptr, player.getFlip());
    // draw a blue rect around the player
    renderer.SetDrawColor(0, 0, 255, 255);
    renderer.DrawRect(Rect(player.getPosX() + player.getBorderLeft(),
                           player.getPosY() + player.getBorderTop(),
                           player.getWidth(), player.getHeight()));
  }
}

void Game::drawZombies() {
  for (auto &enemy : enemies) {
    Texture *sprite = enemy.getCurrentSprite();
    enemy.scrollRight(enemyScrollingOffset);
    renderer.Copy(*sprite,
                  Rect(enemy.getFrameWidth() * enemy.getAnimationFrame(), 0,
                       enemy.getFrameWidth(), enemy.getFrameHeight()),
                  Rect(enemy.getPosX(), enemy.getPosY(), enemy.getFrameWidth(),
                       enemy.getFrameHeight()));
    // TODO: remove the zombies that are too far way from the screen
    // Aca los estoy scrolleando
    // El problema es que son siempre los mismos zombies si no los matas
    if (enemy.getPosX() < -enemy.getFrameWidth()) {
      enemy.scrollLeft(width + enemy.getFrameWidth());
    } else if (enemy.getPosX() > width + enemy.getFrameWidth()) {
      enemy.scrollRight(width + 2 * enemy.getFrameWidth());
    }
    // draw a red rect around the zombie
    renderer.SetDrawColor(255, 0, 0, 255);
    renderer.DrawRect(Rect(enemy.getPosX() + enemy.getBorderLeft(),
                           enemy.getPosY() + enemy.getBorderTop(),
                           enemy.getWidth(), enemy.getHeight()));
  }

  spawnZombie();
  enemyScrollingOffset = 0;
}

void Game::addPlayer(int16_t x, int16_t y, int id) {
  Player other_player(x, y, id, data["IDF"], playerTextures["IDF"]);
  players.push_back(other_player);
}

void Game::addZombie(int16_t x, int16_t y) {
  Zombie zombie(x, y, data["Zombie"], enemyTextures["Zombie"]);
  enemies.push_back(zombie);
}

// Draw to backgrounds to simulate parallax / scrolling effect when player
// gets close to the border
void Game::drawBackground() {
  Rect srcRect = Rect(0, 0, width, height);
  Rect dstRect = Rect(-mapScrollingOffset, 0, width, height);
  // Draw the background
  renderer.Copy(*background, srcRect, dstRect);

  // Draw the background again to simulate parallax
  dstRect.SetX(width - mapScrollingOffset);
  renderer.Copy(*background, srcRect, dstRect);
}

void Game::playerAction(Player &player) {
  const Uint8 *state = SDL_GetKeyboardState(nullptr);
  int x = 0, y = 0;

  if (state[SDL_SCANCODE_LCTRL]) {
    protocol.attack(&was_closed);
    return;
  }

  if (state[SDL_SCANCODE_SPACE]) {
    player.shoot();
    return;
  }

  if (state[SDL_SCANCODE_R]) {
    player.reload();
    return;
  }

  if (state[SDL_SCANCODE_W]) {
    protocol.moveUp(&was_closed);
    return;
  } else if (state[SDL_SCANCODE_S]) {
    protocol.moveDown(&was_closed);
        return;
  }
  if (state[SDL_SCANCODE_A]) {
        protocol.moveLeft(&was_closed);
        return;
          } else if (state[SDL_SCANCODE_D]) {
        protocol.moveRight(&was_closed);
        return;
  }

  // Check if the player is running by pressing shift
  /*if (state[SDL_SCANCODE_LSHIFT]) {
    player.run(x, y);
  } else {
    player.walk(x, y);
  }*/
}

void Game::spawnZombie() {
  if (enemies.size() < 10 * difficulty) {
    int16_t x = rand() % width;
    int16_t y = height * 0.8 + rand() % (int16_t)(height * 0.2 - 128);
    addZombie(x, y);
  }
}

Game::Game(int difficulty, std::string &background_src, Protocol &protocol,
           uint32_t gameId, int playerId, bool &was_closed)
    : difficulty(difficulty),
      protocol(protocol),
      gameId(gameId),
      was_closed(was_closed),
      playerId(playerId) {
  loadData();
  loadTextures();
  loadBackground(background_src);
}

void Game::loadTextures() {
  // IDF
  IDFTextures idf(renderer);
  playerTextures.emplace("IDF", idf);

  // P90
  P90Textures p90(renderer);
  playerTextures.emplace("P90", p90);
  // TODO : Add the rest of the players

  // Load the zombies textures
  ZombieTextures zombie(renderer);
  enemyTextures.emplace("Zombie", zombie);
  // TODO: Add the rest of the zombies
}

void Game::loadData() {
  // Load the players data
  IDFData idfData;
  data.emplace("IDF", idfData);

  P90Data p90Data;
  data.emplace("P90", p90Data);
  // TODO: Add the rest of the players

  // Load the zombies data
  ZombieData zombieData;
  data.emplace("Zombie", zombieData);
  // TODO: Add the rest of the zombies
}
void Game::loadBackground(std::string &background_src) {
  background = new Texture(renderer, background_src);
}
void Game::drawPlayer(Player &player) {
  Texture *sprite = player.getCurrentSprite();
  Rect srcrect(player.getFrameWidth() * player.getAnimationFrame(), 0,
               player.getFrameWidth(), player.getFrameHeight());

  // Check if the player is in the border
  int x = player.getPosX();
  int y = player.getPosY();
  if (player.getPosX() < width * 0.2) {
    x = width * 0.2;
    int diff = width * 0.2 - player.getPosX();
    mapScrollingOffset -= diff;
    enemyScrollingOffset -= diff;
    if (mapScrollingOffset < 0) mapScrollingOffset = width;
    player.scrollLeft(diff);
  } else if (player.getPosX() > width * 0.8) {
    x = width * 0.8;
    int diff = player.getPosX() - width * 0.8;
    mapScrollingOffset += diff;
    enemyScrollingOffset += diff;
    if (mapScrollingOffset > width) mapScrollingOffset = 0;
    player.scrollRight(diff);
  }

  Rect dsrect(x, y, player.getFrameWidth(), player.getFrameHeight());
  SDL_RenderCopyEx(renderer.Get(), sprite->Get(), &srcrect, &dsrect, 0,
                   nullptr, player.getFlip());
  // draw a blue rect around the player
  renderer.SetDrawColor(0, 0, 255, 255);
  renderer.DrawRect(Rect(player.getPosX() + player.getBorderLeft(),
                         player.getPosY() + player.getBorderTop(),
                         player.getWidth(), player.getHeight()));
}
