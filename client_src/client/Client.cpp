//
// Created by ignacio on 6/2/23.
//

#include "Client.h"

#include "Client.h"
#include <iostream>

Client::Client(const char *hostname, const char *port) : protocol(hostname, port) { }

void Client::start() {
  std::string line;

  // First action
  std::getline(std::cin, line);
  bool was_closed = parser.parseFirstAction(line);

  game.StartGame();

  // Next actions
  while (!was_closed && std::getline(std::cin, line)) {
    was_closed = parser.parseNextAction(line);
  }
}