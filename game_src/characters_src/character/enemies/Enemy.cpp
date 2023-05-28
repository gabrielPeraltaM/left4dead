//
// Created by ignacio on 5/27/23.
//

#include "Enemy.h"

Enemy::Enemy(int posX, int posY, const CharacterData &data, CharacterTexture &textures) : Character(data, textures) {
    status.x = posX;
    status.y = posY;
}

void Enemy::attack() {
    setCurrentSprite(textures.attack);
}
