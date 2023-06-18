//
// Created by ignacio on 6/10/23.
//

#include <sstream>
#include <string>
#include <netinet/in.h>
#include "Client.h"
#include "client/game/Game.h"

#define CREATE 0X01
#define JOIN 0X02
#define START 0X03

Client::Client(const char *hostname, const char *port) : peer(hostname, port) {}

void Client::startGame() {
    getFirstAction();
    uint8_t playerId = getPlayerId();
    tentative_start();
    Game game(peer, playerId);
    game.start();
}

void Client::getFirstAction() {
    std::string message;
    std::getline(std::cin, message);

    std::stringstream ss(message);
    std::string command;
    ss >> command;
    std::string argument;
    ss >> argument;

    if (command == "join") {
        int gameId = std::stoi(argument);
        joinGame(gameId);
        std::cout << "Joined game with id: " << gameId << std::endl;
    } else if (command == "create") {
        uint32_t gameId = createGame(argument);
        std::cout << "Game created with id: " << gameId << std::endl;
    } else {
        throw std::runtime_error("Invalid command");
    }
}

uint32_t Client::createGame(std::string &scenarioName) {
    // Send opcode
    const uint8_t opcode = CREATE;
    peer.sendall(&opcode, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    // Send scenario len
    uint16_t scenario_len = scenarioName.length();
    uint16_t scenario_len_n = htons(scenario_len);
    peer.sendall(&scenario_len_n, 2, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    // Send scenario name
    peer.sendall(scenarioName.c_str(), scenario_len, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    // Receive response
    uint32_t response;
    peer.recvall(&response, 4, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    return ntohl(response);
}

uint8_t Client::joinGame(uint32_t gameId) {
    // Send opcode
    const uint8_t opcode = JOIN;
    peer.sendall(&opcode, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    // Send code
    uint32_t code_n = htonl(gameId);
    peer.sendall(&code_n, 4, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    // Receive response
    uint8_t response;
    peer.recvall(&response, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    return response;
}

uint8_t Client::getPlayerId() {
    uint8_t playerId;

    peer.recvall(&playerId, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");

    return playerId;
}

void Client::tentative_start() {
    std::string action;
    while (action != "start") {
        std::cin >> action;
    }
    uint8_t start = START;
    peer.sendall(&start, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");
    uint16_t characters;
    peer.recvall(&characters, 2, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");
    std::vector<uint16_t> buf(characters * 4);
    peer.recvall(buf.data(), characters * 4 * 2, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");
}
