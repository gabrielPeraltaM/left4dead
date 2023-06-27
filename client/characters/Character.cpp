//
// Created by ignacio on 6/9/23.
//

#include "Character.h"

enum Type : int { IDF = 1, SCOUT, P90, INFECTED, JUMPER, SPEAR, VENOM, WITCH };

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

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

void Character::attack() { setStatus(ATTACK); }

void Character::hurt() { setStatus(HURT); }

void Character::die() { setStatus(DIE); }

void Character::reload() { setStatus(RELOAD); }

void Character::idle() { setStatus(IDLE); }

void Character::shoot() { setStatus(SHOOT); }

int Character::getPosX() const { return posX; }

int Character::getPosY() const { return posY; }

int Character::getId() const { return id; }

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

void Character::kill() { dead = true; }

bool Character::isDead() const { return dead; }

Character::Character(int id, int type) : id(id) {
  switch (type) {
    case IDF:
      this->type = "IDF";
      break;
    case SCOUT:
      this->type = "Scout";
      break;
    case P90:
      this->type = "P90";
      break;
    case INFECTED:
      this->type = "Zombie";
      frameSize = 96;
      break;
    case JUMPER:
      this->type = "Jumper";
      frameSize = 96;
      break;
    case SPEAR:
      this->type = "Spear";
      break;
    case VENOM:
      this->type = "Venom";
      break;
    case WITCH:
      this->type = "Witch";
      frameSize = 96;
      break;
    default:
      this->type = "IDF";
      break;
  }
}
int Character::getHealth() const { return health; }

void Character::setHealth(int newHealth) { health = newHealth; }

int Character::getMaxHealth() const { return maxHealth; }

int Character::getAmmo() const { return ammo; }

void Character::setAmmo(int newAmmo) { ammo = newAmmo; }

int Character::getMaxAmmo() const { return maxAmmo; }
void Character::setMaxHealth(int newMaxHealth) {
  maxHealth = newMaxHealth;
  health = newMaxHealth;
}

void Character::setMaxAmmo(int newMaxAmmo) {
  maxAmmo = newMaxAmmo;
  ammo = newMaxAmmo;
}
