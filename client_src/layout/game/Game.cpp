//
// Created by ignacio on 5/24/23.
//

#include "Game.h"

// 23:55 commit
#include "client_src/characters_src/characterTextures/enemies/ZombieTextures.h"

void Game::StartGame() {
  // Initialize SDL
  SDL sdl = SDL(SDL_INIT_VIDEO);

  SDL_GetCurrentDisplayMode(0, &DM);
  width = DM.w;
  height = DM.h;

  // Set the window size
  window.SetSize(width, height);
  gameRenderer.setSize(width, height);

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

    gameProtocol.getPlayerAction();
    // Clear screen
    renderer.Clear();

    // Draw all textures
    gameRenderer.render();

    // Present the screen
    renderer.Present();
    SDL_Delay(1000 / 60);
  }
}

Game::Game(int difficulty, std::string &background_src, Protocol &protocol,
           uint32_t gameId, int playerId, bool &was_closed)
    : difficulty(difficulty),
      protocol(protocol),
      gameId(gameId),
      was_closed(was_closed),
      playerId(playerId),
      background_src(background_src) {
  SDL_SetRenderDrawBlendMode(renderer.Get(), SDL_BLENDMODE_BLEND);
  receiver.start();
}
Game::~Game() {
  receiver.join();
}
