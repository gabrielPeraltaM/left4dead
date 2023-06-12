//
// Created by ignacio on 6/9/23.
//

#include "GameRenderer.h"

void GameRenderer::run() {
    Uint32 t1 = SDL_GetTicks();
    int it = 0;
    int behind = 0;
    int lost = 0;
    const int rate = 1000 / 60;

    int playersRate = 0;
    while (running) {
        // Clear screen
        renderer.SetDrawColor(Color(0, 0, 0, 255));
        renderer.Clear();

        // Show the Background
        backgroundRenderer.render();

        // Show the UI
        uiRenderer.render();

        // Show the players
        playerRenderer.render(it);

        // Update screen
        renderer.Present();

        // Delay
        Uint32 t2 = SDL_GetTicks();
        int rest = rate - (t2 - t1);
        if (rest < 0) {
            behind = -rest;
            lost = behind - behind % rate;
            t1 += lost;
            it += int(lost / rate);
        } else {
            SDL_Delay(rest);
        }
        t1 += rate;

        // Hago que los players se renderizen a 1000 / 60 * 6 => 10 fps
        playersRate++;
        if (playersRate == 6){
            it++;
            playersRate = 0;
        }
    }
}

GameRenderer::GameRenderer(Renderer &renderer, bool &running, std::vector<Character> &characters, int playerId)
        : renderer(renderer),
          running(running),
          characters(
                  characters),
          playerId(playerId) {}