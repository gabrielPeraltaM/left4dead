//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_P90_H
#define LEFT4DEAD_P90_H

#include "Player.h"
class P90 : public Player {
    private:
    public:
    P90(int16_t posX, int16_t posY, CharacterData const &data, CharacterTexture &textures);
};

#endif  // LEFT4DEAD_P90_H
