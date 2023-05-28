//
// Created by ignacio on 5/24/23.
//

#include "Game.h"
#include "game_src/characters_src/characterTextures/players/IDFTextures.h"
#include "game_src/characters_src/characterTextures/enemies/ZombieTextures.h"
#include "game_src/characters_src/characterData/players/IDFData.h"
#include "game_src/characters_src/characterData/enemies/ZombieData.h"
#include "game_src/characters_src/character/players/IDF.h"
#include "game_src/characters_src/character/enemies/Zombie.h"
#include <cstdio>

void Game::StartGame() {
    SDL sdl = SDL(SDL_INIT_VIDEO);
    SDL_DisplayMode DM = SDL_DisplayMode();
    Window window = Window("Left4Dead", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_MAXIMIZED);
    Renderer renderer = Renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load the textures
    std::string background_src = RESOURCE_PATH "/backgrounds/War1/Bright/War.png";
    loadBackground(background_src, renderer);

    loadTextures(renderer);
    loadData();

    // Get the screen size
    SDL_GetCurrentDisplayMode(0, &DM);
    width = DM.w;
    height = DM.h;

    // Set the window size
    window.SetSize(width, height);

    // Add the players
    addPlayer();

    // Add the initial zombies
    spawnZombie();

    // Present changes
    renderer.Present();

    // Game loop
    SDL_Event event;
    bool running = true;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            // Exit game
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        running = false;
                        break;
                    default:
                        movePlayer(players[0]);
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
    for (auto &player: players) {

        Texture *sprite = player.getCurrentSprite();
        Rect srcrect(128*player.getAnimationFrame(), 0, 128,
             128);
        Rect dstrect(player.getPosX(), player.getPosY(), 128,
             128);
        SDL_RenderCopyEx(renderer.Get(),
                         sprite->Get(),
                         &srcrect,
                         &dstrect,
                         0,
                         nullptr,
                         player.getFlip());
        // draw a blue rect around the player
        renderer.SetDrawColor(0, 0, 255, 255);
        renderer.DrawRect(Rect(player.getPosX(), player.getPosY(),
                               player.getFrameWidth(), player.getFrameHeight()));

    }
}

void Game::drawZombies(Renderer & renderer) {
    for (auto &enemy: enemies) {
        Texture *sprite = enemy.getCurrentSprite();
        renderer.Copy(
            *sprite,
            Rect(128 * enemy.getAnimationFrame(), 0, 128, 128),
            Rect(enemy.getPosX(), enemy.getPosY(), 128, 128));
        // draw a red rect around the zombie
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(enemy.getPosX(), enemy.getPosY(),
                               enemy.getFrameWidth(), enemy.getFrameHeight()));
    }

    spawnZombie();
}

void Game::addPlayer() {
    IDF player(500, 900, data["IDF"], textures["IDF"]);
    players.push_back(player);
}

void Game::addZombie(int16_t x, int16_t y) {
    Zombie zombie(x, y, data["Zombie"], textures["Zombie"]);
    enemies.push_back(zombie);
}

void Game::drawBackground(Renderer &renderer) {
    renderer.Copy(*background, Rect(0, 0, width, height),
                  Rect(0, 0, width, height));
}

void Game::movePlayer(Player &player) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    int x = 0, y = 0;

    if (state[SDL_SCANCODE_W]) {
        y = -1;
    } else if (state[SDL_SCANCODE_S]) {
        y = 1;
    }
    if (state[SDL_SCANCODE_A]) {
        x = -1;
    }
    if (state[SDL_SCANCODE_D]) {
        x = 1;
    }

    if (x == 0 && y == 0) {
        player.idle();
        return;
    }

    // Check if the player is running by pressing shift
    if (state[SDL_SCANCODE_LSHIFT]) {
        player.run(x, y);
    } else {
        player.walk(x, y);
    }
}

void Game::spawnZombie() {
    if (enemies.size() < 10 * difficulty && rand() % 100 < 10 * difficulty) {
        int16_t x = rand() % width;
        int16_t y = height * 0.8 + rand() % (int16_t) (height * 0.2 - 100);
        addZombie(x, y);
    }
}

Game::Game(int difficulty, std::string &background_src)
        : difficulty(difficulty) {}

void Game::loadTextures(Renderer &renderer) {
    // Load the players textures
    IDFTextures idf(renderer);
    textures.emplace("IDF", idf);
    // TODO : Add the rest of the players

    // Load the zombies textures
    ZombieTextures zombie(renderer);
    textures.emplace("Zombie", zombie);
    // TODO: Add the rest of the zombies
}

void Game::loadData() {
    // Load the players data
    IDFData idfData;
    data.emplace("IDF", idfData);
    // TODO: Add the rest of the players

    // Load the zombies data
    ZombieData zombieData;
    data.emplace("Zombie", zombieData);
    // TODO: Add the rest of the zombies

}
void Game::loadBackground(std::string &background_src, Renderer &renderer) {
    background = new Texture(renderer, background_src);
}
