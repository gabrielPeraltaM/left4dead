//
// Created by gabriel on 18/05/23.
//

#include "ClientHandler.h"
#include "Login.h"
#include "Commands.h"

void ClientHandler::run() {
    int match_code = -1;
    while (match_code < 0) {
        Login login = protocol.receive_login();
        match_code = login.get_login(matches);
        if (not login.is_joined() && match_code >= 0) {
            protocol.send_match_code(match_code);
            continue;
        }
        if (login.is_joined()) {
            protocol.send_join_successful();
            continue;
        }
        protocol.send_join_fail();
    }
    Match match = matches.join(match_code);
    protocol.send_player_id(match.get_player_id());
    //protocol.receive_start(match);
    Commands commands(protocol, match);
    commands.run();
    is_alive = false;
}

bool ClientHandler::is_dead() {
    return not is_alive;
}

void ClientHandler::kill() {
    keep_talking = false;
    //sk.shutdown(2);
    //sk.close();
}
