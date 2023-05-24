//
// Created by ignacio on 5/24/23.
//

#include "Game.h"

void Game::StartGame() {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Get the screen size
    SDL_GetCurrentDisplayMode(0, &DM);
    width = DM.w;
    height = DM.h;

    // Create window
    Window window("Game",
                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                  width, height,
                  SDL_WINDOW_FULLSCREEN);

    // Create renderer
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set the window size
    window.SetSize(width, height);

    // Add the players
    addPlayer();

    // Add the zombies
    addZombie();

    // Present changes
    renderer.Present();

    // Game loop
    SDL_Event event;
    bool running = true;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            // User exits the game
            if (event.type == SDL_QUIT) {
                running = false;
            }

           // Player movement
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        players[0].moveY(-1);
                        break;
                    case SDLK_s:
                        players[0].moveY(1);
                        break;
                    case SDLK_a:
                        players[0].moveX(-1);
                        break;
                    case SDLK_d:
                        players[0].moveX(1);
                        break;
                    default:
                        break;
                }
            }

        }
        // Clear screen
        renderer.Clear();

        // Draw the background
        drawBackground(renderer);

        // Draw the characters
        drawPlayers(renderer);
        drawZombies(renderer);

        renderer.Present();
        SDL_Delay(1000 / 60);
    }
}

void Game::drawPlayers(Renderer &renderer) {
    for( auto &player : players ) {
        Texture sprite(renderer, RESOURCE_PATH "/Soldier_1/Idle.png");
        renderer.Copy(sprite,
                      Rect(30, 60, 50, 100),
                      Rect(player.getPositionX(), player.getPositionY(), 50, 100));
    }
}

void Game::addPlayer() {
    Player player;
    players.push_back(player);
}

void Game::addZombie() {
    Zombie zombie;
    zombies.push_back(zombie);
}

void Game::drawZombies(Renderer &renderer) {
    for( auto &zombie : zombies ) {
        Texture sprite(renderer, RESOURCE_PATH "/Zombie/Idle.png");
        renderer.Copy(sprite,
                      Rect(30, 30, 50, 100),
                      Rect(zombie.getPositionX(), zombie.getPositionY(), 50, 100));
        // Draw a rectangle around the zombie
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(zombie.getPositionX(), zombie.getPositionY(), 50, 100));
    }

}

void Game::drawBackground(Renderer &renderer) {
    Texture background(renderer, RESOURCE_PATH "/backgrounds/War1/Bright/War.png");
    renderer.Copy(background,
                  Rect(0, 0, width, height),
                  Rect(0, 0, width, height));

}