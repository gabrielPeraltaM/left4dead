//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include <SDL2pp/SDL2pp.hh>
#include "game_src/characters_src/character/enemies/Enemy.h"
#include "game_src/characters_src/character/players/Player.h"
#include "game_src/characters_src/characterData/CharacterData.h"
#include "game_src/characters_src/characterTextures/CharacterTexture.h"
#include "game_src/characters_src/characterTextures/enemies/EnemyTexture.h"
#include "game_src/characters_src/characterTextures/players/PlayerTexture.h"
#include <list>
using namespace SDL2pp;

class Game {
private:
    // SDL variables
    SDL sdl = SDL(SDL_INIT_VIDEO);
    SDL_DisplayMode DM = SDL_DisplayMode();
    Window window = Window("Left4Dead", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);
    int width = 800;
    int height = 600;

    // Background
    Texture* background;
    int mapScrollingOffset = 0;
    int enemyScrollingOffset = 0;

    const int difficulty = 3; // 1 = easy, 2 = medium, 3 = hard

    // Game storage
    std::vector<Player> players;
    std::list<Enemy> enemies;
    std::unordered_map<std::string, PlayerTexture> playerTextures;
    std::unordered_map<std::string, EnemyTexture> enemyTextures; //Los strings van a ser enums
    std::unordered_map<std::string, CharacterData> data;

    // Game functions
    void addPlayer();
    void addZombie(int16_t x, int16_t y);
    void spawnZombie();
    void drawBackground(Renderer &renderer);
    void drawZombies(Renderer &renderer);
    void drawPlayers(Renderer &renderer);
    void playerAction(Player &player);
    void loadTextures(Renderer &renderer);
public:
    Game(int difficulty, std::string &background_src);
    void StartGame();

    void loadData();
    void loadBackground(std::string &background_src, Renderer &renderer);
};


#endif //LEFT4DEAD_GAME_H
