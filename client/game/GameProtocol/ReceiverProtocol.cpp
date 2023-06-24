//
// Created by ignacio on 6/21/23.
//

#include "ReceiverProtocol.h"

#include <netinet/in.h>

#define CHARACTER_ATTRIBUTES_AMOUNT 7
#include "common_src/actions.h"

enum States : uint16_t {
  NOT = 0x04,
  SHOOTING,
  ATTACKING,
  RELOADING,
  DAMAGING,
  DEAD
};

void ReceiverProtocol::handleReceive(std::vector<uint16_t>& state) {
  for (int i = 0; i < numCharacters * CHARACTER_ATTRIBUTES_AMOUNT;
       i += CHARACTER_ATTRIBUTES_AMOUNT) {
    uint16_t playerId = ntohs(state[i]);
    uint16_t x = ntohs(state[i + 1]);
    uint16_t y = ntohs(state[i + 2]);
    uint16_t character_state = ntohs(state[i + 3]);
    uint16_t health = ntohs(state[i + 4]);
    uint16_t ammo = htons(state[i + 5]);

    /*
     * race condition
     * fijensé si hay manera de comunicar al receiver con el renderer que no
     * sea compartiendo el vector de caracteres...
     */
    switch (character_state) {
      case DEAD:
        characters[playerId]->die();
        break;
      case SHOOTING:
        characters[playerId]->shoot();
        break;
      case ATTACKING:
        characters[playerId]->attack();
        break;
      case RELOADING:
        characters[playerId]->reload();
        break;
      case DAMAGING:
        characters[playerId]->hurt();
        break;
      default:
        characters[playerId]->move(x, y);
        break;
    }
  }
}
ReceiverProtocol::ReceiverProtocol(
    std::map<int, std::shared_ptr<Character>>& characters, int numCharacters)
    : characters(characters), numCharacters(numCharacters) {}

void ReceiverProtocol::handleFirstReceive(std::vector<uint16_t>& state) {
  for (int i = 0; i < numCharacters * CHARACTER_ATTRIBUTES_AMOUNT;
       i += CHARACTER_ATTRIBUTES_AMOUNT) {
        uint16_t playerId = ntohs(state[i]);
        uint16_t type = ntohs(state[i + 6]);
        auto *character = new Character(playerId, type);
        characters[playerId] = std::shared_ptr<Character>(character);
  }
}
