//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_ENEMY_H
#define LEFT4DEAD_ENEMY_H


#include "game_src/characters_src/character/Character.h"

class Enemy : public Character {
protected:
public:
    Enemy(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
    void attack() override;
};


#endif //LEFT4DEAD_ENEMY_H
