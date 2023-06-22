//
// Created by ignacio on 6/9/23.
//

#include "Game.h"

#include <sys/socket.h>

void Game::start() {
  SDL sdl = SDL(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_SetRenderDrawBlendMode(renderer.Get(), SDL_BLENDMODE_BLEND);

  SDL_DisplayMode DM = SDL_DisplayMode();
  SDL_GetCurrentDisplayMode(0, &DM);
  SCREEN_WIDTH = DM.w;
  SCREEN_HEIGHT = DM.h;

  // Load music
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  music = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music.mp3");
  Mix_PlayMusic(music, -1);

  // Add initial players
  Character player = Character(200, 900, 0, "IDF");
  characters.push_back(player);

  Character player2 = Character(350, 900, 1, "Scout");
  characters.push_back(player2);

  // Add initial zombies
  Character zombie = Character(800, 900, 2, "Zombie", 96);
  characters.push_back(zombie);

  Character zombie2 = Character(900, 900, 3, "Jumper", 96);
  characters.push_back(zombie2);

  // Game loop
  gameRenderer.start();
  receiver.start();
  sender.start();

  while (running) {
    SDL_Delay(1000 / 60);
  }

  Mix_FreeMusic(music);
  SDL_Quit();

  gameRenderer.join();
  receiver.join();
  sender.join();

}

Game::~Game() {
  socket.shutdown(SHUT_RDWR);
  socket.close();
}

Game::Game(Socket &socket, int playerId) : socket(socket), playerId(playerId) {}
