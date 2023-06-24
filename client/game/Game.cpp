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
  if (mapSelected == 0) {
    music = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music.mp3");
  } else if (mapSelected == 1) {
    music = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music2.mp3");
  } else {
    music = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music3.mp3");
  }
  Mix_PlayMusic(music, -1);

  // Game loop
  gameRenderer.start();
  receiver.start();
  sender.start();

  while (running) {
    SDL_Delay(1000);  // No hace falta que sea tan rapido
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

Game::Game(Socket &socket, int playerId, int numPlayers, int mapSelected,
           int numZombies)
    : socket(socket),
      playerId(playerId),
      numPlayers(numPlayers),
      mapSelected(mapSelected),
      numZombies(numZombies) {}
