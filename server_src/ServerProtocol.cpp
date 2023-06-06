//
// Created by gabriel on 23/05/23.
//

#include "./ServerProtocol.h"
#include "../common_src/liberror.h"
#include <arpa/inet.h>
#include <utility>

#define ACTION_CREATE 1
#define ACTION_JOIN 2

#define JOIN_SUCCESSFUL 0
#define JOIN_FAILURE 1

// change this
#define SEND_POSITION 4

enum OPCODES : uint8_t {
    BROADCAST = 0x03,
    SERVER_BROADCAST = 0x04,
    MOVE = 0x05,
    SHOOT = 0x06,
    ATTACK = 0x07,
    SERVER_MOVE = 0x08,
    SERVER_SHOOT = 0x09,
    SERVER_ATTACK = 0x0A,
};

ServerProtocol::ServerProtocol(Socket sk) : sk(std::move(sk)),
                                            was_closed(false) {}

Login ServerProtocol::receive_login() {
    uint8_t action;
    int s;
    s = sk.recvall(&action, sizeof(action), &was_closed);
    if (s == 0) {
        return {"", (-1)};
    }
    int match_code = 0;
    if (action == ACTION_CREATE) {
        uint16_t name_len;
        s = sk.recvall(&name_len, sizeof(name_len), &was_closed);
        if (s == 0) {
            throw LibError(EPIPE, "The client was disconnected");
        }
        name_len = ntohs(name_len);
        std::string name(name_len, 0);
        s = sk.recvall(name.data(), name_len, &was_closed);
        if (s == 0) {
            throw LibError(EPIPE, "The client was disconnected");
        }
        Login login(std::move(name), match_code);
        login.set_create();
        return login;
    } else if (action == ACTION_JOIN) {
        uint32_t code;
        s = sk.recvall(&code, sizeof(code), &was_closed);
        if (s == 0) {
            throw LibError(EPIPE, "The client was disconnected");
        }
        code = ntohl(code);
        match_code = (int)code;
        Login login("", match_code);
        login.set_join();
        return login;
    }
    return {"", (-1)};
}

void ServerProtocol::send_match_code(int match_code) {
    auto code = (uint32_t)match_code;
    code = htonl(code);
    int s;
    s = sk.sendall(&code, sizeof(code), &was_closed);
    if (s == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
}

void ServerProtocol::send_join_successful() {
    send_byte(JOIN_SUCCESSFUL);
}

void ServerProtocol::send_join_fail() {
    send_byte(JOIN_FAILURE);
}

std::shared_ptr<Action> ServerProtocol::receive_action() {
    uint8_t action;
    int s;
    s = sk.recvall(&action, sizeof(action), &was_closed);
    if (s == 0) {
        return nullptr;
    }
    return nullptr; // change this
}

void ServerProtocol::send_state(const std::shared_ptr<State>& state) {
    uint8_t action = SEND_POSITION;
    int s;
    s = sk.sendall(&action, sizeof(action), &was_closed);
    if (s == 0) {
        return;
    }
}

bool ServerProtocol::closed() const {
    return was_closed;
}

void ServerProtocol::send_byte(uint8_t byte) {
    int s;
    s = sk.sendall(&byte, sizeof(byte), &was_closed);
    if (s == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
}
