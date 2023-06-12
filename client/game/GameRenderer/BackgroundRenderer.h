//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_BACKGROUNDRENDERER_H
#define SDL_PRUEBA_BACKGROUNDRENDERER_H


#include <SDL2pp/SDL2pp.hh>
#include "client/characters/Character.h"

using namespace SDL2pp;
extern int SCREEN_WIDTH;
class BackgroundRenderer {
private:
    Renderer &renderer;
    std::vector<Character> &characters;
    Texture floor = Texture(renderer,
                            "/home/ignacio/Documents/GitHub/sdl_prueba_cliente/background/road.png");
    Texture sky = Texture(renderer,
                          "/home/ignacio/Documents/GitHub/sdl_prueba_cliente/background/sky.png");
    Texture wall = Texture(renderer,
                           "/home/ignacio/Documents/GitHub/sdl_prueba_cliente/background/wall.png");
    Texture houses = Texture(renderer,
                             "/home/ignacio/Documents/GitHub/sdl_prueba_cliente/background/houses.png");
    const int LEVEL_WIDTH = floor.GetWidth();
    Rect camera = {0, 0, LEVEL_WIDTH / 2, floor.GetHeight()};
    Rect skyCamera = {0, 0, LEVEL_WIDTH / 2, floor.GetHeight()};
    Rect housesCamera = {0, 0, LEVEL_WIDTH / 2, floor.GetHeight()};
    int cameraOffset = 0;
    const int playerId;
public:
    BackgroundRenderer(Renderer &renderer, std::vector<Character> &characters, int playerId);
    void render();
    ~BackgroundRenderer();
};


#endif //SDL_PRUEBA_BACKGROUNDRENDERER_H
