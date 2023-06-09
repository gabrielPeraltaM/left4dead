//
// Created by ignacio on 6/7/23.
//

#ifndef LEFT4DEAD_RECEIVER_H
#define LEFT4DEAD_RECEIVER_H

#include <vector>

#include "client_src/characters_src/character/players/Player.h"
#include "client_src/client/Protocol.h"
#include "common_src/thread.h"
class Receiver : public Thread {
 private:
  Protocol *protocol;
  bool &was_closed;
  std::vector<Player> &players;

 public:
  Receiver(Protocol *protocol, bool &was_closed, std::vector<Player> &players);
  void run() override;
};

#endif  // LEFT4DEAD_RECEIVER_H
