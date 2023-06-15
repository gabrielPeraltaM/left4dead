//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_BACKGROUNDRENDERER_H
#define SDL_PRUEBA_BACKGROUNDRENDERER_H


#include <SDL2pp/SDL2pp.hh>
#include "client/characters/Character.h"

using namespace SDL2pp;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
class BackgroundRenderer {
private:
    Renderer &renderer;
    std::vector<Character> &characters;
    Texture floor = Texture(renderer,
                            RESOURCE_PATH "/background/road.png");
    Texture sky = Texture(renderer,
                          RESOURCE_PATH "/background/sky.png");
    Texture wall = Texture(renderer,
                           RESOURCE_PATH "/background/wall.png");
    Texture houses = Texture(renderer,
                             RESOURCE_PATH "/background/houses.png");
    const int LEVEL_WIDTH = floor.GetWidth();
    const int LEVEL_HEIGHT = floor.GetHeight();
    Rect camera = {0, 0, LEVEL_WIDTH / 2, LEVEL_HEIGHT};
    Rect skyCamera = {0, 0, LEVEL_WIDTH / 2, LEVEL_HEIGHT};
    Rect housesCamera = {0, 0, LEVEL_WIDTH / 2, LEVEL_HEIGHT};
    int cameraOffset = 0;
    const int playerId;
public:
    BackgroundRenderer(Renderer &renderer, std::vector<Character> &characters, int playerId);
    void render();
    ~BackgroundRenderer();
};


#endif //SDL_PRUEBA_BACKGROUNDRENDERER_H
