//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H


#include "client_src/characters_src/character/Character.h"
#include "client_src/characters_src/characterTextures/players/PlayerTexture.h"

class Player : public Character {
protected:
public:
    Player(int16_t posX, int16_t posY, CharacterData const &data, CharacterTexture &textures);
    void shoot();
    void reload();
    void update();
    void attack() override;
};


#endif //LEFT4DEAD_PLAYER_H
