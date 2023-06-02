//
// Created by ignacio on 6/2/23.
//

#ifndef LEFT4DEAD_CLIENT_H
#define LEFT4DEAD_CLIENT_H

#include "ActionsParser.h"
#include "Protocol.h"
#include "client_src/layout/game/Game.h"

class Client {
 private:
  Protocol protocol;
  ActionsParser parser = ActionsParser(protocol);
  int difficulty = 1;
  std::string background_src = RESOURCE_PATH "/backgrounds/War1/Pale/War.png";
  Game game = Game(difficulty, background_src);
 public:
  Client(const char *hostname, const char *port);
  ~Client() = default;
  void start();
};

#endif  // LEFT4DEAD_CLIENT_H
