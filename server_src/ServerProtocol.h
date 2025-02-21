//
// Created by gabriel on 23/05/23.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>

#include "../common_src/socket.h"
#include "./Login.h"
#include "Player.h"
#include "State.h"
#include "server_src/actions/Action.h"

class ServerProtocol {
    Socket sk;
    bool was_closed; // maybe it should be atomic

public:
    explicit ServerProtocol(Socket sk);

    Login receive_login();

    void send_match_code(int match_code);

    void send_join_successful();

    void send_join_fail();

    void send_player_id(int player_id);

    void receive_start(Player &player);

    void receive_character_type(Player &player);

    void receive_map_selected(Player &player);

    std::shared_ptr<Action> receive_action();

    void send_state(const std::shared_ptr<State>& state);

    bool closed() const;

private:
    void send_byte(uint8_t byte);

    uint8_t receive_byte();
};

#endif //PROTOCOL_H
