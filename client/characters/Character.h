//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_PRUEBA_CHARACTER_H
#define SDL_PRUEBA_CHARACTER_H


#include <SDL2pp/SDL2pp.hh>
#include <map>

#include "common_src/actions.h"

using namespace SDL2pp;

class Character {
 private:
  int posX = 0;
  int posY = 0;
  int cameraX = 0;
  int cameraY = 0;
  int id;
  actions status = IDLE;
  bool flip = false;
  std::string type = "IDF";
  int frameSize = 128;
  bool dead = false;
  int maxHealth = 100;
  int maxAmmo = 100;
  int health = maxHealth;
  int ammo = maxAmmo;
  void setStatus(actions newStatus);

 public:
  Character(int id, int type);
  ~Character() = default;
  // Actions

  void move(int x, int y);
  void attack();
  void hurt();
  void die();
  void kill();
  void reload();
  void idle();
  void shoot();
  // Getters
  std::string getType() const;
  std::string getAction() const;
  int getPosX() const;
  int getPosY() const;
  int getCameraX() const;
  int getCameraY() const;
  int getId() const;
  int getFrameSize() const;
  int getHealth() const;
  int getAmmo() const;
  int getMaxHealth() const;
  int getMaxAmmo() const;
  SDL_RendererFlip getFlip() const;
  bool isDead() const;
  // Setters
  void setCameraX(int posX);
  void setCameraY(int posY);
  void setHealth(int newHealth);
  void setAmmo(int newAmmo);
  void setMaxHealth(int newMaxHealth);
  void setMaxAmmo(int newMaxAmmo);
};

#endif  // SDL_PRUEBA_CHARACTER_H
