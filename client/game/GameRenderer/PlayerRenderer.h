//
// Created by ignacio on 6/11/23.
//

#ifndef SDL_PRUEBA_PLAYERRENDERER_H
#define SDL_PRUEBA_PLAYERRENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>
#include "client/characters/Character.h"

using namespace SDL2pp;

class PlayerRenderer {
private:
    std::map<std::string, Texture *> textures;
    std::vector<Character> &characters;
    Renderer &renderer;

    void loadTextures();
public:
    PlayerRenderer(std::vector<Character> &characters, Renderer &renderer);
    void render(int it);
    ~PlayerRenderer();

};


#endif //SDL_PRUEBA_PLAYERRENDERER_H
