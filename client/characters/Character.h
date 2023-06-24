//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_PRUEBA_CHARACTER_H
#define SDL_PRUEBA_CHARACTER_H

#include "common_src/actions.h"

#include <SDL2pp/SDL2pp.hh>
#include <map>

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

    void setStatus(actions newStatus);
public:
    Character(int id, const char* type);
    Character(int posX, int posY, int id, const char* type);
    Character(int posX, int posY, int id, const char* type, int frameSize);
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
    actions getStatus() const;
    SDL_RendererFlip getFlip() const;
    bool isDead() const;
    // Setters
    void setCameraX(int posX);
    void setCameraY(int posY);
};


#endif //SDL_PRUEBA_CHARACTER_H
