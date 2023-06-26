//
// Created by gabriel on 18/05/23.
//

#ifndef MATCH_H
#define MATCH_H

#include <atomic>
#include <memory>

#include "StateQueue.h"
#include "server_src/actions/ActionQueue.h"

class Player {
    ActionQueue &actions;
    StateQueue *states;
    std::atomic<bool> finished;
    int player_id;
    int character_type = 0;
    int map_selected = 0;
    bool host;

public:
    Player(ActionQueue &actions, StateQueue *states, int player_id, bool host);

    void send_action(const std::shared_ptr<Action>& action);

    void send_start();

    std::shared_ptr<State> receive_state();

    void finish();

    bool is_finished();

    void set_character_type(int character_type);

    int get_character_type() const;

    void set_map_selected(int map_selected);

    int get_map_selected() const;

    int get_player_id() const;

    bool is_host() const;
};

#endif //MATCH_H
