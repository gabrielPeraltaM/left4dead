#include "Receiver.h"

Receiver::Receiver(Socket &socket, bool &running,
                   std::map<int, std::shared_ptr<Character>> &characters,
                   int numCharacters, bool &isLoadingPlayers, int playerId, uint8_t &gameStatus)
    : socket(socket),
      running(running),
      characters(characters),
      numCharacters(numCharacters),
      isLoadingPlayers(isLoadingPlayers),
      playerId(playerId),
      gameStatus(gameStatus){}

void Receiver::run() {
  // First Receive
  socket.recvall(state.data(), (numCharacters * CHARACTER_ATTRIBUTES_AMOUNT * 2),
                 &was_closed);
  receiverProtocol.handleFirstReceive(state);
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
    std::cout << "Game Status: " << (int)gameStatus << std::endl;
    receiverProtocol.handleReceive(state);
  }
}