//
// Created by gabriel on 18/05/23.
//

#include "ClientHandler.h"
#include "Login.h"
#include "ServerProtocol.h"
#include "Commands.h"

void ClientHandler::run() {
    ServerProtocol protocol;
    int match_code = -1;
    while (match_code < 0) {
        Login login = protocol.receive_login(sk);
        match_code = login.get_login(matches);
        if (not login.is_joined() && match_code >= 0) {
            protocol.send_match_code(sk, match_code);
            continue;
        }
        if (login.is_joined()) {
            protocol.send_join_successful(sk);
            continue;
        }
        protocol.send_join_fail(sk);
    }
    Match match = matches.join(match_code);
    Commands commands(sk, match);
    commands.run();
    is_alive = false;
}

bool ClientHandler::is_dead() {
    return not is_alive;
}

void ClientHandler::kill() {
    keep_talking = false;
    sk.shutdown(2);
    sk.close();
}
