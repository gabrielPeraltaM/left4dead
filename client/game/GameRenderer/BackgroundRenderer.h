//
// Created by ignacio on 6/10/23.
//

#ifndef SDL_PRUEBA_BACKGROUNDRENDERER_H
#define SDL_PRUEBA_BACKGROUNDRENDERER_H

#include <memory>
#include <SDL2pp/SDL2pp.hh>
#include "client/characters/Character.h"

using namespace SDL2pp;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
class BackgroundRenderer {
private:
    Renderer &renderer;
    std::map<int, std::shared_ptr<Character>> &characters;
    const int mapSelected;
    uint8_t &gameStatus;
    std::string mapPath = RESOURCE_PATH "/background" + std::to_string(mapSelected) + "/";
    Texture floor = Texture(renderer,
                            mapPath + "road.png");
    Texture sky = Texture(renderer,
                          mapPath + "sky.png");
    Texture wall = Texture(renderer,
                           mapPath + "wall.png");
    Texture houses = Texture(renderer,
                             mapPath + "/houses.png");
    Texture houses2 = Texture(renderer,
                             mapPath + "/houses2.png");
    const int LEVEL_WIDTH = floor.GetWidth();
    int cameraOffset = 0;
    Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Rect skyCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Rect housesCamera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    const int playerId;
public:
    BackgroundRenderer(Renderer &renderer, std::map<int, std::shared_ptr<Character>> &characters, int playerId, int mapSelected, uint8_t &gameStatus);
    void render();
    ~BackgroundRenderer() = default;
};


#endif //SDL_PRUEBA_BACKGROUNDRENDERER_H
