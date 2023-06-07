//
// Created by ignacio on 6/7/23.
//

#include "Receiver.h"

Receiver::Receiver(Protocol *protocol, bool &was_closed, std::vector<Player> &players) : protocol(protocol), was_closed(was_closed), players(players)  {}

void Receiver::run() {
  while (!was_closed) {
    protocol->receive_status();

  }
}