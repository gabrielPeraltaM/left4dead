#ifndef SDL_PRUEBA_RECEIVER_H
#define SDL_PRUEBA_RECEIVER_H

#include <vector>

#include "ReceiverProtocol.h"
#include "client/characters/Character.h"
#include "common_src/socket.h"
#include "common_src/thread.h"

#define CHARACTER_ATTRIBUTES_AMOUNT 7

class Receiver : public Thread {
 private:
  bool &running;
  bool &isLoadingPlayers;
  const int numCharacters;
  const int playerId;
  std::map<int, std::shared_ptr<Character>> &characters;
  Socket &socket;
  ReceiverProtocol receiverProtocol = ReceiverProtocol(characters, numCharacters, playerId);
  std::vector<uint16_t> state = std::vector<uint16_t>(numCharacters * CHARACTER_ATTRIBUTES_AMOUNT + 1);
  bool was_closed = false;

 public:
  Receiver(Socket &socket, bool &was_closed,
           std::map<int, std::shared_ptr<Character>> &characters, int numCharacters, bool &isLoadingPlayers, int playerId);
  void run() override;
};

#endif  // SDL_PRUEBA_RECEIVER_H
