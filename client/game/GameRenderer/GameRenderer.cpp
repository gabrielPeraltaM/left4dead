//
// Created by ignacio on 6/9/23.
//

#include "GameRenderer.h"

#include <arpa/inet.h>

enum States : uint16_t {
  NOT = 0x04,
  SHOOTING,
  ATTACKING,
  RELOADING,
  DAMAGING,
  DEAD
};

void GameRenderer::run() {
  /*while (isLoadingPlayers) {
    SDL_Delay(10);
  }*/
  Uint32 t1 = SDL_GetTicks();
  int it = 0;
  int behind = 0;
  int lost = 0;
  const int rate = 1000 / 60;
  int playersRate = 0;
  state = states.pop();
  initialize_characters();
  uiRenderer.setPlayer(characters[playerId].get());

  while (running) {
    states.try_pop(state);
    update_characters();
    // Clear screen
    renderer.SetDrawColor(Color(0, 0, 0, 255));
    renderer.Clear();

    // Show the Background
    backgroundRenderer.render();

    // Show the UI
    uiRenderer.render();

    // Show the players
    playerRenderer.render(it);

    // Update screen
    renderer.Present();

    // Delay
    Uint32 t2 = SDL_GetTicks();
    int rest = rate - (t2 - t1);
    if (rest < 0) {  // No deberia pasar nunca
      behind = -rest;
      lost = behind - behind % rate;
      t1 += lost;
      it += int(lost / rate);
    } else {
      SDL_Delay(rest);
    }
    t1 += rate;

    // Hago que los players se renderizen a 1000 / 60 * 6 => 10 fps
    playersRate++;
    if (playersRate == 6) {
      it++;
      playersRate = 0;
    }
  }
}

void GameRenderer::initialize_characters() {
  for (int i = 0; i < numCharacters * CHARACTER_ATTRIBUTES_AMOUNT;
       i += CHARACTER_ATTRIBUTES_AMOUNT) {
    uint16_t id = ntohs(state[i]);
    uint16_t type = ntohs(state[i + 6]);
    auto *character = new Character(id, type);
    if (id == playerId) {
      uint16_t health = ntohs(state[i + 4]);
      uint16_t ammo = htons(state[i + 5]);
      character->setMaxHealth(health);
      character->setMaxAmmo(ammo);
    }
    characters[id] = std::shared_ptr<Character>(character);
  }
}

void GameRenderer::update_characters() {
  for (int i = 0; i < numCharacters * CHARACTER_ATTRIBUTES_AMOUNT;
       i += CHARACTER_ATTRIBUTES_AMOUNT) {
    uint16_t id = ntohs(state[i]);
    uint16_t x = ntohs(state[i + 1]);
    uint16_t y = ntohs(state[i + 2]);
    uint16_t character_state = ntohs(state[i + 3]);
    if (id == playerId) {
      uint16_t health = ntohs(state[i + 4]);
      uint16_t ammo = htons(state[i + 5]);
      characters[id]->setHealth(health);
      characters[id]->setAmmo(ammo);
    }
    switch (character_state) {
      case DEAD:
        characters[id]->die();
        break;
      case SHOOTING:
        characters[id]->shoot();
        break;
      case ATTACKING:
        characters[id]->attack();
        break;
      case RELOADING:
        characters[id]->reload();
        break;
      case DAMAGING:
        characters[id]->hurt();
        break;
      default:
        characters[id]->move(x, y);
        break;
    }
  }
}

GameRenderer::GameRenderer(Renderer &renderer, bool &running, int playerId,
                           int mapSelected, bool &isLoadingPlayers,
                           uint8_t &gameStatus, StateQueue &states,
                           int numCharacters)
    : renderer(renderer),
      running(running),
      playerId(playerId),
      mapSelected(mapSelected),
      isLoadingPlayers(isLoadingPlayers),
      gameStatus(gameStatus),
      numCharacters(numCharacters),
      states(states) {}
