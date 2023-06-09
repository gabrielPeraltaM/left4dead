//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H


#include "client_src/characters_src/characterData/CharacterData.h"
#include "client_src/characters_src/characterTextures/CharacterTexture.h"
#include "client_src/characters_src/characterStatus/CharacterStatus.h"

// Clase principal de la que heredan todos los personajes
class Character {
protected:
    CharacterStatus status;
    CharacterData const &data; // Data y textures son referencias a objetos que se crean en el game
    CharacterTexture &textures;
    Texture *currentSprite;
    int animationFrame = 0;
    int numFrames = 5;
public:
    Character(CharacterData const &data, CharacterTexture &textures);
    Texture *getCurrentSprite() const;
    void setCurrentSprite(Texture *sprite);
    int getFrameWidth() const;
    int getFrameHeight() const;
    int getPosX() const;
    int getPosY() const;
    virtual void attack() = 0;
    void idle();
    void walk(int x, int y);
    void run(int x, int y);
    void die();
    void hurt();
    void takeDamage(int damage);
    void spawn();
    void destroy();
    int getAnimationFrame() const {
        return animationFrame;
    }
    void nextAnimationFrame() {
        animationFrame++;
        if (animationFrame >= numFrames)
          resetAnimationFrame();
    }
    void resetAnimationFrame() {
        animationFrame = 0;
    }
    SDL_RendererFlip getFlip() const {
        return status.flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    }
    int getBorderLeft() const {
        return textures.borderLeft;
    }
    int getWidth() const {
        return textures.width;
    }
    int getBorderTop() const {
        return textures.borderTop;
    }
    int getHeight() const {
        return textures.height;
    }
};


#endif //LEFT4DEAD_CHARACTER_H
