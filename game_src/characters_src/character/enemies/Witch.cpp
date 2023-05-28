//
// Created by ignacio on 5/27/23.
//

#include "Witch.h"
Witch::Witch(int posX, int posY, const CharacterData& data,
             CharacterTexture& textures)
    : Enemy(posX, posY, data, textures) {}
