//
// Created by gabriel on 19/05/23.
//

#ifndef LEFT4DEAD_STATE_H
#define LEFT4DEAD_STATE_H

#include <map>
#include "./game/Character.h"

class State{
public:
    std::map<int, Character*> &elements;

    explicit State(std::map<int, Character*> &elements);
};

#endif //LEFT4DEAD_STATE_H
