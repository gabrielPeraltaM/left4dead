//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_CHARACTERTEXTURE_H
#define LEFT4DEAD_CHARACTERTEXTURE_H

#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

struct CharacterTexture {
    Texture *idle;
    Texture *walk;
    Texture *run;
    Texture *attack;
    Texture *dead;
    Texture *hurt;
    int frameWidth = 128;
    int frameHeight = 128;
    int borderLeft = 30;
    int borderTop = 40;
    int width = 50;
    int height = 50;
    CharacterTexture(Renderer &renderer, const char *srcPath) {
        idle = new Texture(renderer, srcPath + std::string("Idle.png"));
        walk = new Texture(renderer, srcPath + std::string("Walk.png"));
        run = new Texture(renderer, srcPath + std::string("Run.png"));
        dead = new Texture(renderer, srcPath + std::string("Dead.png"));
        hurt = new Texture(renderer, srcPath + std::string("Hurt.png"));
        attack = nullptr;
    }
    CharacterTexture() = default;
};

#endif //LEFT4DEAD_CHARACTERTEXTURE_H
