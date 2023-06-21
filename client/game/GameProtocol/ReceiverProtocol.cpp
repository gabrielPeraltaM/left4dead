//
// Created by ignacio on 6/21/23.
//

#include "ReceiverProtocol.h"

#include <netinet/in.h>

#define CHARACTER_ATTRIBUTES_AMOUNT 6
#define CHARACTER_AMOUNT 4
#include "common_src/actions.h"

enum States : uint16_t {
  NOT = 0x04,
  SHOOTING,
  ATTACKING,
  RELOADING,
  DAMAGING,
  DEAD,
};

void ReceiverProtocol::handleReceive(std::vector<uint16_t>& state) {

  for (int i = 0; i < CHARACTER_AMOUNT * CHARACTER_ATTRIBUTES_AMOUNT;
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
       * MONITOR
     */
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
ReceiverProtocol::ReceiverProtocol(std::vector<Character>& characters) : characters(characters) {}
