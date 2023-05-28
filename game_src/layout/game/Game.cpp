//
// Created by ignacio on 5/24/23.
//

#include "Game.h"

#include <cstdio>

#include "game_src/characters_src/character/enemies/Zombie.h"
#include "game_src/characters_src/character/players/IDF.h"
#include "game_src/characters_src/character/players/P90.h"
#include "game_src/characters_src/characterData/enemies/ZombieData.h"
#include "game_src/characters_src/characterData/players/IDFData.h"
#include "game_src/characters_src/characterData/players/P90Data.h"
#include "game_src/characters_src/characterTextures/enemies/ZombieTextures.h"
#include "game_src/characters_src/characterTextures/players/IDFTextures.h"
#include "game_src/characters_src/characterTextures/players/P90Textures.h"

void Game::StartGame() {
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
                }
            }
        }

        playerAction(players[0]);
        // Clear screen
        renderer.Clear();

        // Draw the background
        drawBackground(renderer);

        // Draw the characters

        // Get the sdl ticks
        drawPlayers(renderer);
        drawZombies(renderer);


        renderer.Present();
        SDL_Delay(1000 / 60);
    }

}

void Game::drawPlayers(Renderer &renderer) {
    for (auto &player: players) {

        Texture *sprite = player.getCurrentSprite();
        Rect srcrect(player.getFrameWidth()*player.getAnimationFrame(), 0, player.getFrameWidth(),
             player.getFrameHeight());

        // Check if the player is in the border
        int x = player.getPosX();
        int y = player.getPosY();

        if (player.getPosX() < width * 0.2) {
            x = width * 0.2;
            int diff = width * 0.2 - player.getPosX();
            mapScrollingOffset -= diff;
            enemyScrollingOffset -= diff;
            if (mapScrollingOffset < 0) mapScrollingOffset = width;
            player.scrollLeft(diff);
        } else if (player.getPosX() > width * 0.8) {
            x = width * 0.8;
            int diff = player.getPosX() - width * 0.8;
            mapScrollingOffset += diff;
            enemyScrollingOffset += diff;
            if (mapScrollingOffset > width) mapScrollingOffset = 0;
            player.scrollRight(diff);
        }

        Rect dstrect(x, y, player.getFrameWidth(),
             player.getFrameHeight());
        SDL_RenderCopyEx(renderer.Get(),
                         sprite->Get(),
                         &srcrect,
                         &dstrect,
                         0,
                         nullptr,
                         player.getFlip());
        // draw a blue rect around the player
        renderer.SetDrawColor(0, 0, 255, 255);
        renderer.DrawRect(Rect(player.getPosX() + player.getBorderLeft(), player.getPosY() + player.getBorderTop(),
                               player.getWidth(), player.getHeight()));

    }
}

void Game::drawZombies(Renderer & renderer) {
    for (auto &enemy: enemies) {
        Texture *sprite = enemy.getCurrentSprite();
        enemy.scrollRight(enemyScrollingOffset);
        renderer.Copy(
            *sprite,
            Rect(enemy.getFrameWidth() * enemy.getAnimationFrame(), 0, enemy.getFrameWidth(), enemy.getFrameHeight()),
            Rect(enemy.getPosX(), enemy.getPosY(), enemy.getFrameWidth(), enemy.getFrameHeight()));
        // TODO: remove the zombies that are too far way from the screen
        // Aca los estoy scrolleando
        // El problema es que son siempre los mismos zombies si no los matas
        if (enemy.getPosX() < -enemy.getFrameWidth()) {
            enemy.scrollLeft(width+ enemy.getFrameWidth());
        } else if (enemy.getPosX() > width + enemy.getFrameWidth()) {
            enemy.scrollRight(width + 2*enemy.getFrameWidth());
        }
        // draw a red rect around the zombie
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(enemy.getPosX() + enemy.getBorderLeft(), enemy.getPosY() + enemy.getBorderTop(),
                               enemy.getWidth(), enemy.getHeight()));
    }

    spawnZombie();
    enemyScrollingOffset = 0;
}

void Game::addPlayer() {
    IDF player(500, 900, data["IDF"], playerTextures["IDF"]);
    players.push_back(player);
}

void Game::addZombie(int16_t x, int16_t y) {
    Zombie zombie(x, y, data["Zombie"], enemyTextures["Zombie"]);
    enemies.push_back(zombie);
}

// Draw to backgrounds to simulate parallax / scrolling effect when player
// gets close to the border
void Game::drawBackground(Renderer &renderer) {
    Rect srcRect = Rect(0, 0, width, height);
    Rect dstRect = Rect(-mapScrollingOffset, 0, width, height);
    // Draw the background
    renderer.Copy(*background, srcRect, dstRect);

    // Draw the background again to simulate parallax
    dstRect.SetX(width - mapScrollingOffset);
    renderer.Copy(*background, srcRect, dstRect);
}

void Game::playerAction(Player &player) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    int x = 0, y = 0;

    if (state[SDL_SCANCODE_LCTRL]) {
        player.attack();
        return;
    }

    if (state[SDL_SCANCODE_SPACE]) {
        player.shoot();
        return;
    }

    if (state[SDL_SCANCODE_R]) {
        player.reload();
        return;
    }

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
    if (enemies.size() < 10 * difficulty) {
        int16_t x = rand() % width;
        int16_t y = height * 0.8 + rand() % (int16_t) (height * 0.2 - 128);
        addZombie(x, y);
    }
}

Game::Game(int difficulty, std::string &background_src)
        : difficulty(difficulty) {}

void Game::loadTextures(Renderer &renderer) {
    // Load the players textures

    // IDF
    IDFTextures idf(renderer);
    playerTextures.emplace("IDF", idf);

    // P90
    P90Textures p90(renderer);
    playerTextures.emplace("P90", p90);
    // TODO : Add the rest of the players

    // Load the zombies textures
    ZombieTextures zombie(renderer);
    enemyTextures.emplace("Zombie", zombie);
    // TODO: Add the rest of the zombies
}

void Game::loadData() {
    // Load the players data
    IDFData idfData;
    data.emplace("IDF", idfData);

    P90Data p90Data;
    data.emplace("P90", p90Data);
    // TODO: Add the rest of the players

    // Load the zombies data
    ZombieData zombieData;
    data.emplace("Zombie", zombieData);
    // TODO: Add the rest of the zombies

}
void Game::loadBackground(std::string &background_src, Renderer &renderer) {
    background = new Texture(renderer, background_src);
}
