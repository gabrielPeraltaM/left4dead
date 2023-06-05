//
// Created by gabriel on 18/05/23.
//

#include "Match.h"

Match::Match(ActionQueue &actions, StateQueue *state) : actions(actions),
                                                        state(state),
                                                        finished(false) {}

void Match::send_action(const std::shared_ptr<Action>& action) {
    actions.push(action);
}

std::shared_ptr<State> Match::receive_state() {
    return state->pop();
}

void Match::finish() {
    finished = true;
}

bool Match::is_finished() {
    return finished;
}
