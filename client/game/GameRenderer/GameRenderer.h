//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_PRUEBA_GAMERENDERER_H
#define SDL_PRUEBA_GAMERENDERER_H


#include "common_src/thread.h"
#include "client/characters/Character.h"
#include "BackgroundRenderer.h"
#include "UIRenderer.h"
#include "PlayerRenderer.h"
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class GameRenderer : public Thread {
private:
    Renderer &renderer;
    bool &running;
    std::vector<Character> &characters;
    const int playerId;
    BackgroundRenderer backgroundRenderer = BackgroundRenderer(renderer, characters, playerId);
    UIRenderer uiRenderer = UIRenderer(renderer, 100, 100, 100, 100);
    PlayerRenderer playerRenderer = PlayerRenderer(characters, renderer);
public:
    GameRenderer(Renderer &renderer, bool &running, std::vector<Character> &characters, int playerId);

    void run() override;
};


#endif //SDL_PRUEBA_GAMERENDERER_H
