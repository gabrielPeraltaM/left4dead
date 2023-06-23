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
 public:
  explicit ReceiverProtocol(std::map<int, std::shared_ptr<Character>> &characters);
  ~ReceiverProtocol() = default;
  void handleReceive(std::vector<uint16_t> &state);
};

#endif  // LEFT4DEAD_RECEIVERPROTOCOL_H
