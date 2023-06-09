//
// Created by ignacio on 5/27/23.
//

#include "Player.h"

#include "client_src/characters_src/characterStatus/players/PlayerStatus.h"

Player::Player(int16_t posX, int16_t posY, int playerId, CharacterData const &data, CharacterTexture &textures) : playerId(playerId), Character(data, textures) {
    status.x = posX;
    status.y = posY;
}

void Player::attack() {
    if (status.state == State::ATTACK) {
      nextAnimationFrame();
    } else {
      resetAnimationFrame();
    }
    status.state = State::ATTACK;
    setCurrentSprite(textures.attack);
}

void Player::shoot() {
    if (status.state == State::SHOOT) {
      nextAnimationFrame();
    } else {
      resetAnimationFrame();
    }
    status.state = State::SHOOT;

    PlayerTexture &playerTextures = static_cast<PlayerTexture &>(textures);
    setCurrentSprite(playerTextures.shoot);
}

void Player::reload() {
    if (status.state == State::RELOAD) {
      nextAnimationFrame();
    } else {
      resetAnimationFrame();
    }
    status.state = State::RELOAD;

    PlayerTexture &playerTextures = static_cast<PlayerTexture &>(textures);
    setCurrentSprite(playerTextures.reload);
}

void Player::update() {
    //setCurrentSprite(textures.update);
}
int Player::getPlayerId() const {
    return playerId;
}
