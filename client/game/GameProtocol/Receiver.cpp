//
// Created by ignacio on 6/10/23.
//

#include "Receiver.h"
#include <netinet/in.h>
#include <vector>

#define CHARACTER_ATTRIBUTES_AMOUNT 5

Receiver::Receiver(Socket &socket, bool &running,
                   std::vector<Character> &characters)
    : socket(socket), running(running), characters(characters) {}

void Receiver::run() {
  std::vector<uint16_t> state(4 * CHARACTER_ATTRIBUTES_AMOUNT); // change this 'n'
  bool was_closed = false;

  while (running) {
    // Receive action
    socket.recvall(state.data(), 4 * CHARACTER_ATTRIBUTES_AMOUNT * 2, &was_closed); // change sz
    if (was_closed) {
      running = false;
      break;
    }
    for (int i = 0; i < 4 * CHARACTER_ATTRIBUTES_AMOUNT; i += CHARACTER_ATTRIBUTES_AMOUNT) {
      uint16_t playerId = ntohs(state[i]);
      uint16_t x = ntohs(state[i + 1]);
      uint16_t y = ntohs(state[i + 2]);
      uint16_t shooting = ntohs(state[i + 3]);
      uint16_t dead = ntohs(state[i + 4]);
      if (dead) {
          characters.at(playerId).die();
      } else if (shooting) {
        characters.at(playerId).shoot();
      } else {
        characters.at(playerId).move(x, y);
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
character.attack();
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
