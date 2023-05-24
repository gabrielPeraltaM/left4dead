//
// Created by ignacio on 5/24/23.
//

#include "Character.h"

Character::Character(uint16_t positionX, uint16_t positionY, uint8_t health, uint8_t speed, uint8_t damage,
                     uint8_t attackSpeed, uint8_t attackRange, uint8_t attackCooldown, uint16_t width, uint16_t height,
                     const char *spritePath) :
                     positionX(positionX), positionY(positionY), health(health), speed(speed), damage(damage),
                     attackSpeed(attackSpeed), attackRange(attackRange), attackCooldown(attackCooldown),
                     width(width), height(height), spritePath(spritePath) { }

uint16_t Character::getWidth() const {
    return width;
}

uint16_t Character::getHeight() const {
    return height;
}

uint16_t Character::getPositionX() const {
    return positionX;
}

bool Character::moveX(int16_t x) {
    if( positionX + x * speed < 0 ) {
        return false;
    }
    this->positionX += x * speed;
    return true;
}

uint16_t Character::getPositionY() const {
    return positionY;
}

bool Character::moveY(int16_t y) {
    if( positionY + y * speed < 0 ) {
        return false;
    }
    this->positionY += y * speed;
    return true;
}

bool Character::moveUp() {
    return moveY(-1);
}

bool Character::moveDown() {
    return moveY(1);
}

bool Character::moveLeft() {
    return moveX(-1);
}

bool Character::moveRight() {
    return moveX(1);
}

uint8_t Character::getHealth() const {
    return health;
}

void Character::reduceHealth(uint8_t dmgReceived) {
    if( dmgReceived > health ) {
        health = 0;
        die();
        return;
    }
    health -= dmgReceived;
}

uint8_t Character::getSpeed() const {
    return speed;
}

uint8_t Character::getDamage() const {
    return damage;
}

uint8_t Character::getAttackSpeed() const {
    return attackSpeed;
}

uint8_t Character::getAttackRange() const {
    return attackRange;
}

uint8_t Character::getAttackCooldown() const {
    return attackCooldown;
}

void Character::move(int16_t newPosX, int16_t newPosY) {
    if( newPosX < 0 || newPosY < 0 ) {
        return;
    }
    moveX(newPosX);
    moveY(newPosY);
}

State Character::getState() const {
    return state;
}

void Character::setState(State newState) {
    state = newState;
}

std::string Character::getSpritePath() const {
    return spritePath;
}