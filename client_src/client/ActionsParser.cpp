//
// Created by ignacio on 5/5/23.
//

#include "ActionsParser.h"
#include <iostream>
#include <sstream>

#define CREATE "create"
#define JOIN "join"
#define BROADCAST "broadcast"
#define READ "read"
#define LEAVE "leave"

ActionsParser::ActionsParser(Protocol &protocol) : protocol(protocol) {}

bool ActionsParser::parseFirstAction(const std::string &message) {
    std::stringstream ss(message);
    std::string command;
    ss >> command;

    if (command == CREATE) {
        std::string scenario_name;
        ss >> scenario_name;
        uint16_t scenario_len = scenario_name.length();
        uint32_t gameId = protocol.create(scenario_len, scenario_name.c_str(), &was_closed);

        std::cout << "Created match: " << gameId << std::endl;
    } else if (command == JOIN) {
        std::string code_string;
        ss >> code_string;
        uint32_t code = std::stoi(code_string);
        uint8_t status = protocol.join(code, &was_closed);
        if (status == 0) {
            std::cout << "Joined to match: " << code_string << std::endl;
        } else if (status == 1) {
            std::cout << "Match does not exist: " << code_string << std::endl;
        } else {
            throw std::runtime_error("Invalid status");
        }
    } else {
        std::cerr << "Invalid command" << std::endl; // Acá no quiero que se lanze una excepción
    }
    return was_closed;
}

bool ActionsParser::parseNextAction(const std::string &message) {
    std::stringstream ss(message);
    std::string command;
    ss >> command;

    if (command == BROADCAST) {
        std::string msg;
        ss >> msg;
        uint16_t msg_len = msg.length();
        protocol.broadcast(msg_len, msg.c_str(), &was_closed);
    } else if (command == READ) {
        int n;
        ss >> n;

        for (int i = 0; i < n; i++) {
            std::string msg = protocol.read_one(&was_closed);
            std::cout << "Broadcasted: " << msg << std::endl;
        }
    } else if (command == LEAVE) {
        protocol.leave(&was_closed);
    }

    return was_closed;
}
