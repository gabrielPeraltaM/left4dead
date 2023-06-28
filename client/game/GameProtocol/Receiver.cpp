#include "Receiver.h"

#include <netinet/in.h>

#include <vector>

Receiver::Receiver(Socket &socket, bool &running,
                   std::map<int, std::shared_ptr<Character>> &characters,
                   int numCharacters, bool &isLoadingPlayers, int playerId)
    : socket(socket),
      running(running),
      characters(characters),
      numCharacters(numCharacters),
      isLoadingPlayers(isLoadingPlayers),
      playerId(playerId) {}

void Receiver::run() {
  // First Receive
  socket.recvall(state.data(), ((numCharacters * CHARACTER_ATTRIBUTES_AMOUNT) + 1) * 2,
                 &was_closed);
  receiverProtocol.handleFirstReceive(state);
  isLoadingPlayers = false;
  // Loop
  while (running) {
    socket.recvall(state.data(), ((numCharacters * CHARACTER_ATTRIBUTES_AMOUNT) + 1) * 2,
                   &was_closed);
    if (was_closed) {
      running = false;
      break;
    }

    receiverProtocol.handleReceive(state);
  }
}