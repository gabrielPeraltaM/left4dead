//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_UIRENDERER_H
#define SDL_PRUEBA_UIRENDERER_H


#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class UIRenderer {
private:
    Renderer &renderer;
    int health;
    int ammo;
    int score;
    int stamina;
public:
    UIRenderer(Renderer &renderer, int health, int ammo, int score, int stamina);
    void render();
    void update(int health, int ammo, int score, int stamina);
};


#endif //SDL_PRUEBA_UIRENDERER_H
