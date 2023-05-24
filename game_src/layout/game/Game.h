//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include "../../characters/player/Player.h"
#include "../../characters/zombie/Zombie.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class Game {
private:
    SDL_DisplayMode DM = SDL_DisplayMode();
    int width = 800;
    int height = 600;
    std::string background_src = RESOURCE_PATH "/backgrounds/War1/Bright/War.png";
    const int difficulty = 3; // 1 = easy, 2 = medium, 3 = hard
    std::vector<Zombie> zombies;
    std::vector<Player> players;
    void addPlayer();
    void addZombie(int16_t x, int16_t y);
    void spawnZombie();
    void drawBackground(Renderer &renderer);
    void drawZombies(Renderer &renderer);
    void drawPlayers(Renderer &renderer);
    void movePlayer(Player &player);
public:
    Game() = default;
    Game(int difficulty, std::string &background_src);
    void StartGame();
};


#endif //LEFT4DEAD_GAME_H
