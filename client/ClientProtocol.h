//
// Created by ignacio on 6/23/23.
//

#ifndef LEFT4DEAD_CLIENTPROTOCOL_H
#define LEFT4DEAD_CLIENTPROTOCOL_H

#include <cstdint>
#include <string>

#include "common_src/socket.h"
class ClientProtocol {
 private:
  Socket &socket;
  bool &was_closed;
  bool host = false;
 public:
  ClientProtocol(Socket &socket, bool &was_closed);
  uint32_t createGame(std::string &scenarioName);
  uint8_t joinGame(uint32_t gameId);
  uint8_t getPlayerId();
  void sendCharacterType(uint8_t characterType);
  void startGame();
};

#endif  // LEFT4DEAD_CLIENTPROTOCOL_H
