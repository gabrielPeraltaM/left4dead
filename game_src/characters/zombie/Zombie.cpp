//
// Created by ignacio on 5/24/23.
//

#include "Zombie.h"

Zombie::Zombie() : Character(300, 50, 100, 8, 5, 10, 1, 50, 100, RESOURCE_PATH "/Zombie/", 30, 30) { }

Zombie::Zombie(int16_t posX, int16_t posY) : Character(posX, posY, 100, 8, 5, 10, 1, 50, 100, RESOURCE_PATH "/Zombie/", 30, 30) { }

void Zombie::attack() {

}

void Zombie::die() {

}

void Zombie::spawn() {

}

void Zombie::update() {

}

void Zombie::destroy() {

}

void Zombie::getCharacterType() {

}
