//
// Created by ignacio on 5/27/23.
//

#include "Character.h"
#include <algorithm>

Character::Character(CharacterData const &data, CharacterTexture &textures) : data(data), textures(textures), currentSprite(textures.idle) {}

void Character::walk(int x, int y) {
    if (status.state == State::WALK) {
      nextAnimationFrame();
    } else {
      resetAnimationFrame();
    }
    status.state = State::WALK;
    setCurrentSprite(textures.walk);
    if (x < 0) {
      status.flip = true;
    } else if (x > 0) {
      status.flip = false;
    }
    status.x += x * data.speed;
    status.y += y * data.speed;
}

void Character::die() {
    status.state = State::DEAD;
    setCurrentSprite(textures.dead);
}

void Character::takeDamage(int damage) {
    status.health -= damage;
    if (status.health <= 0) {
        hurt();
    }
}

void Character::spawn() {
    status.health = data.health;
    status.state = State::IDLE;
}

void Character::destroy() {
    die();
}

void Character::hurt() {
    status.state = State::HURT;
    setCurrentSprite(textures.hurt);
}

int Character::getFrameWidth() const {
    return textures.frameWidth;
}

int Character::getFrameHeight() const {
    return textures.frameHeight;
}

int Character::getPosX() const {
    return status.x;
}

int Character::getPosY() const {
    return status.y;
}

void Character::idle() {
    if (status.state == State::IDLE) {
        nextAnimationFrame();
    } else {
        resetAnimationFrame();
    }
    status.state = State::IDLE;
    setCurrentSprite(textures.idle);
}

void Character::run(int x, int y) {
    if (status.state == State::RUN) {
        nextAnimationFrame();
    } else {
        resetAnimationFrame();
    }
    status.state = State::RUN;
    status.x += x * data.speed * 2;
    status.y += y * data.speed * 2;
    setCurrentSprite(textures.run);
    if (x < 0) {
        status.flip = true;
    } else if (x > 0) {
        status.flip = false;
    }
}
void Character::setCurrentSprite(Texture *sprite) {
    numFrames = sprite->GetWidth() / 128;
    currentSprite = sprite;
}
Texture *Character::getCurrentSprite() const {
        return currentSprite;
}