//
// Created by gabriel on 18/05/23.
//

#ifndef MATCH_H
#define MATCH_H

#include "ActionQueue.h"
#include "StateQueue.h"
#include <atomic>
#include <memory>

class Player {
    ActionQueue &actions;
    StateQueue *states;
    std::atomic<bool> finished;
    int player_id;
    bool host;

public:
    Player(ActionQueue &actions, StateQueue *states, int player_id, bool host);

    void send_action(const std::shared_ptr<Action>& action);

    void send_start();

    std::shared_ptr<State> receive_state();

    void finish();

    bool is_finished();

    int get_player_id() const;

    bool is_host() const;
};

#endif //MATCH_H
