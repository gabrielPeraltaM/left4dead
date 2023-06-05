#include "Client.h"
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include "Client.h"

#define CREATE "create"
#define JOIN "join"
#define BROADCAST "broadcast"
#define READ "read"
#define LEAVE "leave"

Client::Client(const char *hostname, const char *port) : protocol(hostname, port) { }

void Client::start(int difficulty, std::string background_src) {
  std::string message = "create 0";
  uint32_t gameId = parseFirstAction(message);
  Game game(difficulty, background_src);
}

uint32_t Client::parseFirstAction(const std::string &message) {
  std::stringstream ss(message);
  std::string command;
  ss >> command;
  uint32_t gameId;

  if (command == CREATE) {
    std::string scenario_name;
    ss >> scenario_name;
    uint16_t scenario_len = scenario_name.length();
    gameId = protocol.create(scenario_len, scenario_name.c_str(), &was_closed);
    std::cout << "Created match: " << gameId << std::endl;

  } else if (command == JOIN) {
    std::string code_string;
    ss >> code_string;
    gameId = std::stoi(code_string);
    uint8_t status = protocol.join(gameId, &was_closed);
    if (status == 0) {
      std::cout << "Joined to match: " << code_string << std::endl;
    } else if (status == 1) {
      std::cout << "Match does not exist: " << code_string << std::endl;
      throw std::runtime_error("Match does not exist");
    } else {
      throw std::runtime_error("Invalid status");
    }

  } else {
    std::cerr << "Invalid command" << std::endl;
    throw std::runtime_error("Invalid command");
  }
  return gameId;
}
