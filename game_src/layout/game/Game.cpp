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

            // Exit game
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: case SDLK_q:
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
    for( auto &player : players ) {
        std::string spritePath = player.getSpritePath();
        switch (player.getState()) {
            case State::IDLE:
                spritePath += "/Idle.png";
                break;
            case State::WALK:
                spritePath += "/Walk.png";
                break;
            case State::RUN:
                spritePath += "/Run.png";
                break;
            case State::ATTACK:
                spritePath += "/Attack.png";
                break;
            case State::HURT:
                spritePath += "/Hurt.png";
                break;
            case State::DEAD:
                spritePath += "/Dead.png";
                break;
        }

        Texture sprite(renderer, spritePath);
        renderer.Copy(sprite,
                      Rect(30, 60, player.getWidth(), player.getHeight()),
                      Rect(player.getPositionX(), player.getPositionY(), player.getWidth(), player.getHeight()));
    }
}

void Game::addPlayer() {
    Player player;
    players.push_back(player);
}

void Game::addZombie() {
    Zombie zombie(50, 900);
    zombies.push_back(zombie);
}

void Game::drawZombies(Renderer &renderer) {
    for( auto &zombie : zombies ) {
        Texture sprite(renderer, zombie.getSpritePath() + "/Idle.png");
        renderer.Copy(sprite,
                      Rect(30, 30, zombie.getWidth(), zombie.getHeight()),
                      Rect(zombie.getPositionX(), zombie.getPositionY(), zombie.getWidth(), zombie.getHeight()));
        // Draw a rectangle around the zombie
        renderer.SetDrawColor(255, 0, 0, 255);
        renderer.DrawRect(Rect(zombie.getPositionX(), zombie.getPositionY(), zombie.getWidth(), zombie.getHeight()));
    }

}

void Game::drawBackground(Renderer &renderer) {
    Texture background(renderer, RESOURCE_PATH "/backgrounds/War1/Bright/War.png");
    renderer.Copy(background,
                  Rect(0, 0, width, height),
                  Rect(0, 0, width, height));

}

void Game::movePlayer(Player &player) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    bool isMoving = false;

    if(state[SDL_SCANCODE_W]){
        player.moveUp();
        isMoving = true;
    }
    if(state[SDL_SCANCODE_S]){
        player.moveDown();
        isMoving = true;
    }
    if(state[SDL_SCANCODE_A]){
        player.moveLeft();
        isMoving = true;
    }
    if(state[SDL_SCANCODE_D]){
        player.moveRight();
        isMoving = true;
    }

    if (!isMoving) {
        player.setState(State::IDLE);
        return;
    }

    // Check if the player is running by pressing shift
    if(state[SDL_SCANCODE_LSHIFT]){
        player.setState(State::RUN);
    } else {
        player.setState(State::WALK);
    }

}
