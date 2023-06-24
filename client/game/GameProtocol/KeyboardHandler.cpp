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
  bool isRunning = false;
  if (keys.at(SDLK_LSHIFT)) {
        isRunning = true;
  }

  uint8_t movement = 0;
  int direction = getDirection();
  switch (direction) {
    case 1:
      movement = isRunning ? RUN_LEFT : MOVE_LEFT;
      break;
    case 2:
      movement = isRunning ? RUN_RIGHT : MOVE_RIGHT;
      break;
    case 4:
      movement = isRunning ? RUN_UP : MOVE_UP;
      break;
    case 8:
      movement = isRunning ? RUN_DOWN : MOVE_DOWN;
      break;
    case 5:
      movement = isRunning ? RUN_UP_LEFT : MOVE_UP_LEFT;
      break;
    case 6:
      movement = isRunning ? RUN_UP_RIGHT : MOVE_UP_RIGHT;
      break;
    case 9:
      movement = isRunning ? RUN_DOWN_LEFT : MOVE_DOWN_LEFT;
      break;
    case 10:
      movement = isRunning ? RUN_DOWN_RIGHT : MOVE_DOWN_RIGHT;
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
