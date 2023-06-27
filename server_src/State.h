//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_H
#define LEFT4DEAD_STATE_H

#include <vector>
#include <cstdint>
#include "./game/Character.h"

#define CONTINUE 0
#define WIN 1
#define LOOSE 2

class State{
public:
    std::vector<uint16_t> elements;
    uint16_t characters;
    uint16_t zombies;
    int match_state;

    State(std::vector<uint16_t> elements, uint16_t characters, uint16_t zombies);

    void set_continue();

    void set_win();

    void set_loose();
};

#endif //LEFT4DEAD_STATE_H
