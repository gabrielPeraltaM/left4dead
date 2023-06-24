//
// Created by ignacio on 6/9/23.
//

#include "Character.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

Character::Character(int id, const char *type)
    : posX(0), posY(0), id(id), type(type) {}

Character::Character(int posX, int posY, int id, const char *type)
    : posX(posX), posY(posY), id(id), type(type) {}

void Character::move(int x, int y) {
  if (posX == x && posY == y) {
    setStatus(IDLE);
    return;
  }
  setStatus(MOVE_UP);
  if (posX - x > 0) {
    flip = true;
  } else if (posX - x < 0) {
    flip = false;
  }
  posX = x;
  posY = y;
}

void Character::run(int x, int y) {
  move(x, y);
  if (status != IDLE)
    setStatus(RUN_UP);
}

void Character::attack() { setStatus(ATTACK); }

void Character::hurt() { setStatus(HURT); }

void Character::die() { setStatus(DIE); }

void Character::reload() { setStatus(RELOAD); }

void Character::idle() { setStatus(IDLE); }

void Character::shoot() { setStatus(SHOOT); }

int Character::getPosX() const { return posX; }

int Character::getPosY() const { return posY; }

int Character::getId() const { return id; }

actions Character::getStatus() const { return status; }

SDL_RendererFlip Character::getFlip() const {
  return flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void Character::setCameraX(int newCameraX) { cameraX = newCameraX; }

void Character::setCameraY(int newCameraY) {
  cameraY =
      SCREEN_HEIGHT + (775 - newCameraY - frameSize) * SCREEN_HEIGHT / 1080;
}

int Character::getCameraX() const { return cameraX * SCREEN_WIDTH / 1920; }

int Character::getCameraY() const { return cameraY; }

std::string Character::getType() const { return type; }

std::string Character::getAction() const {
  switch (status) {
    case IDLE:
      return "Idle";
    case MOVE_LEFT:
    case MOVE_RIGHT:
    case MOVE_UP:
    case MOVE_DOWN:
    case MOVE_DOWN_LEFT:
    case MOVE_DOWN_RIGHT:
    case MOVE_UP_LEFT:
    case MOVE_UP_RIGHT:
      return "Walk";
    case ATTACK:
      return "Attack";
    case HURT:
      return "Hurt";
    case DIE:
      return "Dead";
    case RELOAD:
      return "Recharge";
    case SHOOT:
      return "Shot_1";
    default:
      return "Idle";
  }
}

void Character::setStatus(actions newStatus) { status = newStatus; }

int Character::getFrameSize() const { return frameSize; }

Character::Character(int posX, int posY, int id, const char *type,
                     int frameSize)
    : posX(posX), posY(posY), id(id), type(type), frameSize(frameSize) {}

void Character::kill() { dead = true; }

bool Character::isDead() const { return dead; }
