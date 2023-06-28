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
    uint16_t id = ntohs(state[i]);
    uint16_t x = ntohs(state[i + 1]);
    uint16_t y = ntohs(state[i + 2]);
    uint16_t character_state = ntohs(state[i + 3]);
    if (id == playerId) {
      uint16_t health = ntohs(state[i + 4]);
      uint16_t ammo = htons(state[i + 5]);
      characters[id]->setHealth(health);
      characters[id]->setAmmo(ammo);
    }
    switch (character_state) {
      case DEAD:
        characters[id]->die();
        break;
      case SHOOTING:
        characters[id]->shoot();
        break;
      case ATTACKING:
        characters[id]->attack();
        break;
      case RELOADING:
        characters[id]->reload();
        break;
      case DAMAGING:
        characters[id]->hurt();
        break;
      default:
        characters[id]->move(x, y);
        break;
    }
  }
}
ReceiverProtocol::ReceiverProtocol(
    std::map<int, std::shared_ptr<Character>>& characters, int numCharacters,
    int playerId)
    : characters(characters),
      numCharacters(numCharacters),
      playerId(playerId) {}

void ReceiverProtocol::handleFirstReceive(std::vector<uint16_t>& state) {
  for (int i = 0; i < numCharacters * CHARACTER_ATTRIBUTES_AMOUNT;
       i += CHARACTER_ATTRIBUTES_AMOUNT) {
    uint16_t id = ntohs(state[i]);
    uint16_t type = ntohs(state[i + 6]);
    auto* character = new Character(id, type);
    if (id == playerId) {
      uint16_t health = ntohs(state[i + 4]);
      uint16_t ammo = htons(state[i + 5]);
      character->setMaxHealth(health);
      character->setMaxAmmo(ammo);
    }
    characters[id] = std::shared_ptr<Character>(character);
  }

}
