//
// Created by gabriel on 18/05/23.
//

#include "Match.h"

Match::Match(Match &&other) {
    this->group = other.group;
    this->player = other.player;
    this->finished = other.is_finished();
}

bool Match::is_finished() {
    return finished;
}
