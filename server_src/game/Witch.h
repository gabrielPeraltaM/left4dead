//
// Created by gabriel on 21/06/23.
//

#ifndef LEFT4DEAD_WITCH_H
#define LEFT4DEAD_WITCH_H

#include "Zombie.h"
#include <map>
#include <random>

class Witch : public Zombie {
    std::map<int, Character*> &zombies;
    std::uniform_int_distribution<int> dist;
    std::random_device rd;

public:
    Witch(int pos_x, int pos_y, std::map<int, Character*> &zombies, int &dead_zombies);

    void interact() override;

    void scream();

    void stop_zombies();

    void receive_damage(int damage) override;
};

#endif //LEFT4DEAD_WITCH_H
