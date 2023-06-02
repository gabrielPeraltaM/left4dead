//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H


#include "Enemy.h"
#include "client_src/characters_src/characterData/CharacterData.h"
#include "client_src/characters_src/characterTextures/CharacterTexture.h"

class Zombie : public Enemy {
    private:
    public:
    Zombie(int posX, int posY, CharacterData const &data, CharacterTexture &textures);
};


#endif //LEFT4DEAD_ZOMBIE_H
