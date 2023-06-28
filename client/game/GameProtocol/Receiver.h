#ifndef SDL_PRUEBA_RECEIVER_H
#define SDL_PRUEBA_RECEIVER_H

#include <vector>
#include "../../StateQueue.h"
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
  uint8_t &gameStatus;
  Socket &socket;
  StateQueue &states;
  //ReceiverProtocol receiverProtocol = ReceiverProtocol(numCharacters);
  std::vector<uint16_t> state = std::vector<uint16_t>(numCharacters * CHARACTER_ATTRIBUTES_AMOUNT);
  bool was_closed = false;

 public:
  Receiver(Socket &socket, bool &was_closed, int numCharacters, bool &isLoadingPlayers, int playerId, uint8_t &gameStatus, StateQueue &states);
  void run() override;
};

#endif  // SDL_PRUEBA_RECEIVER_H
