//
// Created by ignacio on 6/2/23.
//

#include "GameProtocol.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

GameProtocol::GameProtocol(Protocol& protocol, bool &was_closed) :protocol(protocol), was_closed(was_closed) {}

void GameProtocol::getPlayerAction() {
  const Uint8 *state = SDL_GetKeyboardState(nullptr);

  if (state[SDL_SCANCODE_LCTRL]) {
    protocol.attack(&was_closed);
    return;
  }

  if (state[SDL_SCANCODE_SPACE]) {
    protocol.shoot(&was_closed);
    return;
  }

  if (state[SDL_SCANCODE_R]) {
    protocol.reload(&was_closed);
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
}
