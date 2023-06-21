//
// Created by ignacio on 6/21/23.
//

#ifndef LEFT4DEAD_RECEIVERPROTOCOL_H
#define LEFT4DEAD_RECEIVERPROTOCOL_H

#include <cstdint>
#include <vector>
#include "client/characters/Character.h"
class ReceiverProtocol {
  std::vector<Character> &characters;
 public:
  ReceiverProtocol(std::vector<Character> &characters);
  ~ReceiverProtocol() = default;
  void handleReceive(std::vector<uint16_t> &state);
};

#endif  // LEFT4DEAD_RECEIVERPROTOCOL_H
