//
// Created by ignacio on 6/2/23.
//

#ifndef LEFT4DEAD_GAMEPROTOCOL_H
#define LEFT4DEAD_GAMEPROTOCOL_H

#include "client_src/client/Protocol.h"
class GameProtocol {
 private:
  Protocol &protocol;
  bool &was_closed;
 public:
  GameProtocol(Protocol &protocol, bool &was_closed);
  void getPlayerAction();
  ~GameProtocol() = default;
};

#endif  // LEFT4DEAD_GAMEPROTOCOL_H
