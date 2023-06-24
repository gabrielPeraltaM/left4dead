#include "KeyboardHandler.h"

#include <SDL_keycode.h>

#include "common_src/actions.h"
KeyboardHandler::KeyboardHandler() {
  keys[SDLK_w] = false;
  keys[SDLK_a] = false;
  keys[SDLK_s] = false;
  keys[SDLK_d] = false;
  keys[SDLK_r] = false;
  keys[SDLK_SPACE] = false;
  keys[SDLK_LSHIFT] = false;
  keys[SDLK_LCTRL] = false;
}
void KeyboardHandler::setPressed(int key) { keys[key] = true; }

void KeyboardHandler::setReleased(int key) { keys[key] = false; }

int KeyboardHandler::getDirection() const {
  int direction = 0;
  if (keys.at(SDLK_w)) {
    direction |= 4;
  }
  if (keys.at(SDLK_a)) {
    direction |= 1;
  }
  if (keys.at(SDLK_s)) {
    direction |= 8;
  }
  if (keys.at(SDLK_d)) {
    direction |= 2;
  }
  return direction;
}

uint8_t KeyboardHandler::getMovement() const {
  uint8_t movement = 0;
  int direction = getDirection();
  switch (direction) {
    case 1:
      movement = MOVE_LEFT;
      break;
    case 2:
      movement = MOVE_RIGHT;
      break;
    case 4:
      movement = MOVE_UP;
      break;
    case 8:
      movement = MOVE_DOWN;
      break;
    case 5:
      movement = MOVE_UP_LEFT;
      break;
    case 6:
      movement = MOVE_UP_RIGHT;
      break;
    case 9:
      movement = MOVE_DOWN_LEFT;
      break;
    case 10:
      movement = MOVE_DOWN_RIGHT;
      break;
    default:
      break;
  }
  return movement;
}

uint8_t KeyboardHandler::getAction() const {
  uint8_t action = getMovement();

  if (keys.at(SDLK_r)) {
    action = RELOAD;
  }
  if (keys.at(SDLK_SPACE)) {
    action = SHOOT;
  }

  if (keys.at(SDLK_LCTRL)) {
    action = ATTACK;
  }
  return action;
}
