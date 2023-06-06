//
// Created by ignacio on 6/2/23.
//

#ifndef LEFT4DEAD_CLIENT_H
#define LEFT4DEAD_CLIENT_H

#include "Protocol.h"
#include "client_src/layout/game/Game.h"

class Client {
 private:
  Protocol protocol;
  bool was_closed = false;
 public:
  Client(const char *hostname, const char *port);
  ~Client() = default;
  void start(int difficulty, std::string background_src);
  uint32_t parseFirstAction(const std::string &message);
};

#endif  // LEFT4DEAD_CLIENT_H
