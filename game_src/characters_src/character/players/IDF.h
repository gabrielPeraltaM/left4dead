//
// Created by ignacio on 5/27/23.
//

#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H


#include "Player.h"

class IDF : public Player {
    private:
    public:
    IDF(int16_t posX, int16_t posY, CharacterData const &data, CharacterTexture &textures);
};


#endif //LEFT4DEAD_IDF_H
