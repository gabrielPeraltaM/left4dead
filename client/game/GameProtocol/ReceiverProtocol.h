//
// Created by ignacio on 6/21/23.
//

#ifndef LEFT4DEAD_RECEIVERPROTOCOL_H
#define LEFT4DEAD_RECEIVERPROTOCOL_H

#include <cstdint>
#include <vector>
#include "client/characters/Character.h"
#include <memory>
class ReceiverProtocol {
  std::map<int, std::shared_ptr<Character>> &characters;
  const int numCharacters;
  const int playerId;
 public:
  ReceiverProtocol(std::map<int, std::shared_ptr<Character>> &characters, int numCharacters, int playerId);
  ~ReceiverProtocol() = default;
  void handleReceive(std::vector<uint16_t> &state);
  void handleFirstReceive(std::vector<uint16_t> &state);
};

#endif  // LEFT4DEAD_RECEIVERPROTOCOL_H
