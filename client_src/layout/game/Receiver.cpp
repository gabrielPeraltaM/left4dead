//
// Created by ignacio on 6/7/23.
//

#include "Receiver.h"

Receiver::Receiver(Protocol *protocol, bool &was_closed,
                   std::vector<Player> &players)
    : protocol(protocol), was_closed(was_closed), players(players) {}

void Receiver::run() {
  uint8_t action;
  int playerId;
  while (!was_closed) {
    playerId = protocol->receive_player(&was_closed);
    playerId--;
    std::cout << "Player: " << playerId << std::endl;

    action = protocol->receive_action(&was_closed);
    std::cout << "Action: " << (int)action << std::endl;

    switch (action) {
      case OPCODES::IDLE:
        players[playerId].idle();
        break;
      case OPCODES::MOVE_UP:
        players[playerId].walk(0, -1);
        break;
      case OPCODES::MOVE_DOWN:
        players[playerId].walk(0, 1);
        break;
      case OPCODES::MOVE_LEFT:
        players[playerId].walk(-1, 0);
        break;
      case OPCODES::MOVE_RIGHT:
        players[playerId].walk(1, 0);
        break;
      case OPCODES::ATTACK:
        players[playerId].attack();
        break;
      case OPCODES::SHOOT:
        players[playerId].shoot();
        break;
      case OPCODES::RELOAD:
        players[playerId].reload();
        break;
      default:
        break;
    }
  }
}