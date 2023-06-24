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
  RUNNING
};

void ReceiverProtocol::handleReceive(std::vector<uint16_t>& state) {
  uint16_t playerId = ntohs(state[0]);
  uint16_t x = ntohs(state[1]);
  uint16_t y = ntohs(state[2]);
  uint16_t character_state = ntohs(state[3]);
  uint16_t health = ntohs(state[4]);
  uint16_t ammo = htons(state[5]);
  /*
   * race condition
   * fijensé si hay manera de comunicar al receiver con el renderer que no
   * sea compartiendo el vector de caracteres...
   */
  switch (character_state) {
    case DEAD:
      characters.at(playerId)->die();
      break;
    case SHOOTING:
      characters.at(playerId)->shoot();
      break;
    case ATTACKING:
      characters.at(playerId)->attack();
      break;
    case RELOADING:
      characters.at(playerId)->reload();
      break;
    case DAMAGING:
      characters.at(playerId)->hurt();
      break;
    default:
      characters.at(playerId)->move(x, y);
      break;
  }
}
ReceiverProtocol::ReceiverProtocol(
    std::map<int, std::shared_ptr<Character>>& characters)
    : characters(characters) {}
