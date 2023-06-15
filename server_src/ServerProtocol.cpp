//
// Created by gabriel on 23/05/23.
//

#include "./ServerProtocol.h"
#include "../common_src/liberror.h"
#include "ActionMove.h"
#include "ActionShoot.h"
#include <arpa/inet.h>
#include <utility>
#include <cmath>

#define ACTION_CREATE 1
#define ACTION_JOIN 2

#define JOIN_SUCCESSFUL 0
#define JOIN_FAILURE 1

#define MOVE_SIZE 5

enum OPCODES : uint8_t {
    //IDLE = 0x04,
    MOVE_UP = 0x05,
    MOVE_DOWN = 0x06,
    MOVE_LEFT = 0x07,
    MOVE_RIGHT = 0x08,
    SHOOTING = 0x09,
    //ATTACK = 0x0A,
    //RELOAD = 0x0B,
    MOVE_UP_LEFT = 0x0C,
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

        case SHOOTING:
                return std::make_shared<ActionShoot>();

        default:
            // change this
                std::cout << (int)action << std::endl;
                throw LibError(EINVAL, "Invalid action");
            return nullptr;
    }
}

void ServerProtocol::send_state(const std::shared_ptr<State>& state) {
    uint16_t buf[16];
    int pos = 0;
    for (auto element : state->elements) {
        auto character_id = (uint16_t)element.first;
        auto *character = element.second;
        auto pos_x = (uint16_t)character->get_pos_x();
        auto pos_y = (uint16_t)character->get_pos_y();
        auto character_state = (uint16_t)character->get_state();

        character_id = htons(character_id);
        pos_x = htons(pos_x);
        pos_y = htons(pos_y);
        character_state = htons(character_state);
        buf[pos++] = character_id;
        buf[pos++] = pos_x;
        buf[pos++] = pos_y;
        buf[pos++] = character_state;
        character->stop_shooting();
    }
    if (sk.sendall(&buf, sizeof(buf), &was_closed) == 0) {
        throw LibError(EPIPE, "The client was disconnected");
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
