//
// Created by ignacio on 6/9/23.
//

#include "Game.h"

#include <sys/socket.h>

void Game::start() {
  SDL sdl = SDL(SDL_INIT_VIDEO);
  SDL_SetRenderDrawBlendMode(renderer.Get(), SDL_BLENDMODE_BLEND);

  SDL_DisplayMode DM = SDL_DisplayMode();
  SDL_GetCurrentDisplayMode(0, &DM);
  SCREEN_WIDTH = DM.w;
  SCREEN_HEIGHT = DM.h;

  // Add initial players
  Character player = Character(200, 900, 0, "IDF");
  characters.push_back(player);

  Character player2 = Character(350, 900, 1, "Scout");
  characters.push_back(player2);

  // Add initial zombies
  Character zombie = Character(500, 950, 2, "Zombie", 96);
  characters.push_back(zombie);

  Character zombie2 = Character(900, 950, 3, "Jumper", 96);
  characters.push_back(zombie2);

  // Game loop
  gameRenderer.start();
  receiver.start();
  sender.start();

  SDL_Event event;

  while (running) {
    // Handle events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = false;
            break;
        }
      } else if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
            SCREEN_WIDTH = event.window.data1;
            SCREEN_HEIGHT = event.window.data2;
            break;
          case SDL_WINDOWEVENT_CLOSE:
            running = false;
            break;
        }
      }
    }

    // Delay
    SDL_Delay(1000 / 60);
  }

  SDL_Quit();
}

Game::~Game() {
  socket.shutdown(SHUT_RDWR);
  socket.close();
}

Game::Game(Socket &socket, int playerId) : socket(socket), playerId(playerId) {}
