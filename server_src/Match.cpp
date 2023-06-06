//
// Created by gabriel on 18/05/23.
//

#include "Match.h"

Match::Match(ActionQueue &actions, StateQueue *states, int player_id) : actions(actions),
                                                         states(states),
                                                         finished(false),
                                                         player_id(player_id) {}

void Match::send_action(const std::shared_ptr<Action>& action) {
    actions.push(action);
}

std::shared_ptr<State> Match::receive_state() {
    return states->pop();
}

void Match::finish() {
    finished = true;
    states->close();
}

bool Match::is_finished() {
    return finished;
}

int Match::get_player_id() const {
    return player_id;
}
