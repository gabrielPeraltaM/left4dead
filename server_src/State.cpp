//
// Created by gabriel on 13/06/23.
//

#include "State.h"

#include <utility>

State::State(std::vector<uint16_t> elements, uint16_t characters,
             uint16_t zombies)
    : elements(std::move(elements)), characters(characters), zombies(zombies), match_state(CONTINUE) {}

void State::set_continue() {
    match_state = CONTINUE;
    elements.push_back(CONTINUE);
}

void State::set_win() {
    match_state = WIN;
    elements.push_back(WIN);
}

void State::set_loose() {
    match_state = LOOSE;
    elements.push_back(LOOSE);
}
