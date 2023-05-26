//
// Created by ignacio on 5/24/23.
//

#include "Game.h"
#include "../../characters/player/IDF.h"
#include "../../characters/player/P90.h"

void Game::StartGame() {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);

    // Get the screen size
    SDL_GetCurrentDisplayMode(0, &DM);
    width = DM.w;
    height = DM.h;

    // Create window
    Window window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                  height, SDL_WINDOW_FULLSCREEN);

    // Create renderer
    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Set the window size
    window.SetSize(width, height);

    // Add the players
    addPlayer();

    // Add the zombies
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
        std::string spritePath = player.getSpritePath();

        Texture sprite(renderer, spritePath);
        renderer.Copy(sprite,
                      Rect(player.getFrameWidth(), player.getFrameHeight(),
                           player.getWidth(), player.getHeight()),
                      Rect(player.getPositionX(), player.getPositionY(),
                           player.getWidth(), player.getHeight()));
        // draw a red rect around the player
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(player.getPositionX(), player.getPositionY(),
                               player.getWidth(), player.getHeight()));
    }
}

void Game::addPlayer() {
    IDF player(400, 900);
    players.push_back(player);
}

void Game::addZombie(int16_t x, int16_t y) {
    Zombie zombie(x, y);
    zombies.push_back(zombie);
}

void Game::drawZombies(Renderer &renderer) {
    for (auto &zombie: zombies) {
        Texture sprite(renderer, zombie.getSpritePath());
        renderer.Copy(
                sprite,
                Rect(zombie.getFrameWidth(), zombie.getFrameHeight(), zombie.getWidth(),
                     zombie.getHeight()),
                Rect(zombie.getPositionX(), zombie.getPositionY(), zombie.getWidth(),
                     zombie.getHeight()));
        // draw a red rect around the zombie
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(zombie.getPositionX(), zombie.getPositionY(),
                               zombie.getWidth(), zombie.getHeight()));
    }

    spawnZombie();
}

void Game::drawBackground(Renderer &renderer) {
    Texture background(renderer, background_src);
    renderer.Copy(background, Rect(0, 0, width, height),
                  Rect(0, 0, width, height));
}

void Game::movePlayer(Player &player) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    bool isMoving = false;

    if (state[SDL_SCANCODE_W]) {
        player.moveUp();
        isMoving = true;
    }
    if (state[SDL_SCANCODE_S]) {
        player.moveDown();
        isMoving = true;
    }
    if (state[SDL_SCANCODE_A]) {
        player.moveLeft();
        isMoving = true;
    }
    if (state[SDL_SCANCODE_D]) {
        player.moveRight();
        isMoving = true;
    }

    if (!isMoving) {
        player.setState(State::IDLE);
        return;
    }

    // Check if the player is running by pressing shift
    if (state[SDL_SCANCODE_LSHIFT]) {
        player.setState(State::RUN);
    } else {
        player.setState(State::WALK);
    }
}

void Game::spawnZombie() {
    if (zombies.size() < 10 * difficulty && rand() % 100 < 10 * difficulty) {
        int16_t x = rand() % width;
        int16_t y = height * 0.8 + rand() % (int16_t) (height * 0.2 - 100);
        addZombie(x, y);
    }
}

Game::Game(int difficulty, std::string &background_src)
        : difficulty(difficulty), background_src(background_src) {}
