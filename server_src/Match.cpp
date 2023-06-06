//
// Created by gabriel on 18/05/23.
//

#include "Match.h"

Match::Match(ActionQueue &actions, StateQueue *states) : actions(actions),
                                                         states(states),
                                                         finished(false) {}

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
