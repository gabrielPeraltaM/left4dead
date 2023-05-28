//
// Created by ignacio on 5/27/23.
//

#include "Player.h"



Player::Player(int16_t posX, int16_t posY, CharacterData const &data, CharacterTexture &textures) : Character(data, textures) {
    status.x = posX;
    status.y = posY;
}

void Player::attack() {
    setCurrentSprite(textures.attack);
}

void Player::shoot() {
    //setCurrentSprite(textures.shoot);
}

void Player::reload() {
    //setCurrentSprite(textures.reload);
}

void Player::update() {
    //setCurrentSprite(textures.update);
}