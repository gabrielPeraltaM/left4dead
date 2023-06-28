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
  socket.recvall(state.data(), (numCharacters * CHARACTER_ATTRIBUTES_AMOUNT * 2),
                 &was_closed);
  receiverProtocol.handleFirstReceive(state);
  uint8_t gameStatus = 0;
  socket.recvall(&gameStatus, 1, &was_closed);

  isLoadingPlayers = false;
  // Loop
  while (running && gameStatus == 0) {
    socket.recvall(state.data(), (numCharacters * CHARACTER_ATTRIBUTES_AMOUNT * 2),
                   &was_closed);
    if (was_closed) {
      running = false;
      break;
    }
    socket.recvall(&gameStatus, 1, &was_closed);

    receiverProtocol.handleReceive(state);
  }
}