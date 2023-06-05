//
// Created by gabriel on 18/05/23.
//

#ifndef MATCH_H
#define MATCH_H

#include "ActionQueue.h"
#include "StateQueue.h"
#include <atomic>
#include <memory>

class Match {
    ActionQueue &actions;
    StateQueue *state;
    std::atomic<bool> finished;

public:
    Match(ActionQueue &actions, StateQueue *state);

    void send_action(const std::shared_ptr<Action>& action);

    std::shared_ptr<State> receive_state();

    void finish();

    bool is_finished();
};

#endif //MATCH_H
