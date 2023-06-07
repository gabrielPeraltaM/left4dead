//
// Created by ignacio on 6/7/23.
//

#include "Receiver.h"

Receiver::Receiver(Protocol *protocol, bool &was_closed, std::vector<Player> &players) : protocol(protocol), was_closed(was_closed), players(players)  {}

void Receiver::run() {
  uint8_t action;
  int playerId;
  while (!was_closed) {
    playerId = protocol->receive_player(&was_closed);
    std::cout << "Player: " << playerId << std::endl;


    action = protocol->receive_action(&was_closed);
    std::cout << "Action: " << (int)action << std::endl;

    /* Aca checkeo que mandaste y hago lo que corresponda */
     //* players[playerId].shoot();
  }
}