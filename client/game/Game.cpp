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
  music2 = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music2.mp3");
  music3 = Mix_LoadMUS(RESOURCE_PATH "/Media/bg-music3.mp3");

  // Load initial Players
  for (int i = 0; i < numPlayers; i++) {
    auto *character = new Character(i, "IDF");
    characters[i] = std::shared_ptr<Character>(character);
  }

  // Game loop
  gameRenderer.start();
  receiver.start();
  sender.start();

  while (running) {
    // Check if music has finished and start the next one
    if (!Mix_PlayingMusic()) {
      musicIndex++;
      if (musicIndex == 3) {
        musicIndex = 0;
      }
      if (musicIndex == 0) {
        Mix_PlayMusic(music, 1);
      } else if (musicIndex == 1) {
        Mix_PlayMusic(music2, 1);
      } else if (musicIndex == 2) {
        Mix_PlayMusic(music3, 1);
      }
    }
    SDL_Delay(1000);  // No hace falta que sea tan rapido
  }

  Mix_FreeMusic(music);
  Mix_FreeMusic(music2);
  Mix_FreeMusic(music3);
  SDL_Quit();

  gameRenderer.join();
  receiver.join();
  sender.join();
}

Game::~Game() {
  socket.shutdown(SHUT_RDWR);
  socket.close();
}

Game::Game(Socket &socket, int playerId, int numPlayers, int mapSelected)
    : socket(socket),
      playerId(playerId),
      numPlayers(numPlayers),
      mapSelected(mapSelected) {}
