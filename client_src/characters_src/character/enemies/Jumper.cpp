//
// Created by ignacio on 5/27/23.
//

#include "Jumper.h"
Jumper::Jumper(int posX, int posY, const CharacterData& data,
               CharacterTexture& textures)
    : Enemy(posX, posY, data, textures) {}
