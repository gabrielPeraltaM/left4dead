//
// Created by gabriel on 23/05/23.
//

#include "./ServerProtocol.h"
#include "../common_src/liberror.h"
#include "ActionMove.h"
#include "ActionShoot.h"
#include "ActionAttack.h"
#include "ActionReload.h"
#include <arpa/inet.h>
#include <utility>
#include <cmath>

#define ACTION_CREATE 1
#define ACTION_JOIN 2
#define ACTION_START 3

#define JOIN_SUCCESSFUL 0
#define JOIN_FAILURE 1

#define MOVE_SIZE 5

enum OPCODES : uint8_t {
    IDLE = 0x04,
    MOVE_UP = 0x05,
    MOVE_DOWN = 0x06,
    MOVE_LEFT = 0x07,
    MOVE_RIGHT = 0x08,
    SHOOT = 0x09,
    ATTACK = 0x0A,
    RELOAD = 0x0B,
    MOVE_UP_LEFT,
    MOVE_UP_RIGHT,
    MOVE_DOWN_LEFT,
    MOVE_DOWN_RIGHT,
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

void ServerProtocol::send_player_id(int player_id) {
    send_byte((uint8_t)player_id);
}

void ServerProtocol::receive_start(Player &match) {
    uint8_t start = -1;
    while (start != ACTION_START) {
        start = receive_byte();
    }
    auto state = match.receive_state();
    uint16_t characters = htons(state->characters);
    if (sk.sendall(&characters, sizeof(characters), &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
    auto elements = state->elements;
    if (sk.sendall(elements.data(), elements.size() * 2, &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
}

std::shared_ptr<Action> ServerProtocol::receive_action() {
    uint8_t action;
    int s;
    s = sk.recvall(&action, sizeof(action), &was_closed);
    if (s == 0) {
        return nullptr;
    }
    switch (action) {
        case MOVE_UP:
            return std::make_shared<ActionMove>(0, MOVE_SIZE);

        case MOVE_DOWN:
            return std::make_shared<ActionMove>(0, -MOVE_SIZE);

        case MOVE_LEFT:
            return std::make_shared<ActionMove>(-MOVE_SIZE, 0);

        case MOVE_RIGHT:
            return std::make_shared<ActionMove>(MOVE_SIZE, 0);

        case MOVE_DOWN_LEFT:
            return std::make_shared<ActionMove>(-MOVE_SIZE/sqrt(2), -MOVE_SIZE/sqrt(2));

        case MOVE_DOWN_RIGHT:
            return std::make_shared<ActionMove>(MOVE_SIZE/sqrt(2), -MOVE_SIZE/sqrt(2));

        case MOVE_UP_LEFT:
            return std::make_shared<ActionMove>(-MOVE_SIZE/sqrt(2), MOVE_SIZE/sqrt(2));

        case MOVE_UP_RIGHT:
            return std::make_shared<ActionMove>(MOVE_SIZE/sqrt(2), MOVE_SIZE/sqrt(2));

        case SHOOT:
            return std::make_shared<ActionShoot>();

        case ATTACK:
            return std::make_shared<ActionAttack>();

        case RELOAD:
            return std::make_shared<ActionReload>();

        default:
            // change this
            return nullptr;
    }
}

void ServerProtocol::send_state(const std::shared_ptr<State>& state) {
    if (sk.sendall(state->elements.data(), state->elements.size() * 2, &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
}

bool ServerProtocol::closed() const {
    return was_closed;
}

void ServerProtocol::send_byte(uint8_t byte) {
    if (sk.sendall(&byte, sizeof(byte), &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
}

uint8_t ServerProtocol::receive_byte() {
    uint8_t byte;
    if (sk.recvall(&byte, sizeof(byte), &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
    }
    return byte;
}
