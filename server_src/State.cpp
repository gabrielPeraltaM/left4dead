//
// Created by gabriel on 13/06/23.
//

#include "State.h"

#include <utility>

State::State(std::vector<uint16_t> elements, uint16_t characters,
             uint16_t zombies)
    : elements(std::move(elements)), characters(characters), zombies(zombies) {}
