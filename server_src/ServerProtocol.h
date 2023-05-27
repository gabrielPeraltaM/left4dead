//
// Created by gabriel on 23/05/23.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "./Login.h"
#include "../common_src/socket.h"

class ServerProtocol {
public:
    Login receive_login(Socket &sk);

    void send_match_code(Socket& sk, int match_code);

    void send_join_successful(Socket& sk);

    void send_join_fail(Socket& sk);

private:
    void send_byte(Socket &sk, uint8_t byte);
};

#endif //PROTOCOL_H
