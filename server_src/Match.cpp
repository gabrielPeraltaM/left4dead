//
// Created by gabriel on 18/05/23.
//

#include "Match.h"

Match::Match(Match &&other) noexcept {
    this->group = other.group;
    this->player = other.player;
    this->finished = other.is_finished();
}

void Match::finish() {
    finished = true;
}

bool Match::is_finished() {
    return finished;
}
