//
// Created by gabriel on 23/05/23.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "./Login.h"
#include "../common_src/socket.h"

class ServerProtocol {
    Socket sk;

public:
    explicit ServerProtocol(Socket sk);

    Login receive_login();

    void send_match_code(int match_code);

    void send_join_successful();

    void send_join_fail();

private:
    void send_byte(uint8_t byte);
};

#endif //PROTOCOL_H
