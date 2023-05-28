//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_GAME_H
#define LEFT4DEAD_GAME_H

#include "game_src/characters_src/characterTextures/CharacterTexture.h"
#include "game_src/characters_src/characterData/CharacterData.h"
#include "game_src/characters_src/character/players/Player.h"
#include "game_src/characters_src/character/enemies/Enemy.h"
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;

class Game {
private:
    // SDL variables
    int width = 800;
    int height = 600;
    Texture* background;

    const int difficulty = 3; // 1 = easy, 2 = medium, 3 = hard

    // Game storage
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    std::unordered_map<std::string, CharacterTexture> textures; //Los strings van a ser enums
    std::unordered_map<std::string, CharacterData> data;

    // Game functions
    void addPlayer();
    void addZombie(int16_t x, int16_t y);
    void spawnZombie();
    void drawBackground(Renderer &renderer);
    void drawZombies(Renderer &renderer);
    void drawPlayers(Renderer &renderer);
    void movePlayer(Player &player);
    void loadTextures(Renderer &renderer);
public:
    Game(int difficulty, std::string &background_src);
    void StartGame();

    void loadData();
    void loadBackground(std::string &background_src, Renderer &renderer);
};


#endif //LEFT4DEAD_GAME_H
