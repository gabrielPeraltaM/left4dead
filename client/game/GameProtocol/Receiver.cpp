//
// Created by ignacio on 6/10/23.
//

#include "Receiver.h"

#include <netinet/in.h>

#include <vector>

#define CHARACTER_ATTRIBUTES_AMOUNT 6

enum States : uint16_t {
  NOT = 0x04,
  SHOOTING,
  ATTACKING,
  RELOADING,
  DAMAGING,
  DEAD,
};

Receiver::Receiver(Socket &socket, bool &running,
                   std::vector<Character> &characters)
    : socket(socket), running(running), characters(characters) {}

void Receiver::run() {
  std::vector<uint16_t> state(4 *
                              CHARACTER_ATTRIBUTES_AMOUNT);  // change this 'n'
  bool was_closed = false;

  while (running) {
    // Receive action
    socket.recvall(state.data(), 4 * CHARACTER_ATTRIBUTES_AMOUNT * 2,
                   &was_closed);  // change sz
    if (was_closed) {
      running = false;
      break;
    }
    for (int i = 0; i < 4 * CHARACTER_ATTRIBUTES_AMOUNT;
         i += CHARACTER_ATTRIBUTES_AMOUNT) {
      uint16_t playerId = ntohs(state[i]);
      uint16_t x = ntohs(state[i + 1]);
      uint16_t y = ntohs(state[i + 2]);
      uint16_t character_state = ntohs(state[i + 3]);
      uint16_t health = ntohs(state[i + 4]);
      switch (character_state) {
        case DEAD:
          characters.at(playerId).die();
          break;
        case SHOOTING:
          characters.at(playerId).shoot();
          break;
        case ATTACKING:
          characters.at(playerId).attack();
          break;
        case RELOADING:
          characters.at(playerId).reload();
          break;
        case DAMAGING:
          characters.at(playerId).hurt();
          break;
        default:
          characters.at(playerId).move(x, y);
          break;
      }
    }
  }
}

/*
 * // Receive id
socket.recvall(&playerId, sizeof(playerId), &was_closed);
playerId--;
if (was_closed) {
    running = false;
    break;
}

// Do action
Character &character = characters.at(playerId);

switch (action) {
case actions::MOVE_UP:
character.move(0, -1);
break;
case actions::MOVE_DOWN:
character.move(0, 1);
break;
case actions::MOVE_LEFT:
character.move(-1, 0);
break;
case actions::MOVE_RIGHT:
character.move(1, 0);
break;
case actions::MOVE_DOWN_LEFT:
character.move(-1, 1);
break;
case actions::MOVE_DOWN_RIGHT:
character.move(1, 1);
break;
case actions::MOVE_UP_LEFT:
character.move(-1, -1);
break;
case actions::MOVE_UP_RIGHT:
character.move(1, -1);
break;
case actions::IDLE:
character.idle();
break;
case actions::ATTACK:
character.shooting();
break;
case actions::HURT:
character.hurt();
break;
case actions::DIE:
character.die();
break;
case actions::SHOOT:
character.shoot();
break;
case actions::RELOAD:
character.reload();
break;
default:
break;
}
 */
