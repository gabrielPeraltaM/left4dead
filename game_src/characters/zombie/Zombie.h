//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H


#include "../Character.h"

class Zombie : public Character {
private:
public:
    Zombie();
    Zombie(int16_t posX, int16_t posY);
    void attack() override;
    void die() override;
    void spawn() override;
    void update() override;
    void destroy() override;

};


#endif //LEFT4DEAD_ZOMBIE_H
