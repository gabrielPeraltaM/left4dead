//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_H
#define LEFT4DEAD_STATE_H

#include <vector>
#include <cstdint>
#include "./game/Character.h"

class State{
public:
    std::vector<uint16_t> elements;
    uint16_t characters;
    uint16_t zombies;

    State(std::vector<uint16_t> elements, uint16_t characters, uint16_t zombies);
};

#endif //LEFT4DEAD_STATE_H
