#include "Receiver.h"

#include <netinet/in.h>

#include <vector>
#define CHARACTER_ATTRIBUTES_AMOUNT 7

Receiver::Receiver(Socket &socket, bool &running,
                   std::map<int, std::shared_ptr<Character>> &characters)
    : socket(socket), running(running), characters(characters) {}

void Receiver::run() {
  std::vector<uint16_t> state(4 *
                              CHARACTER_ATTRIBUTES_AMOUNT);  // change this 'n'
  bool was_closed = false;

  while (running) {
    // Receive action
    socket.recvall(state.data(), 4 * CHARACTER_ATTRIBUTES_AMOUNT * 2,
                   &was_closed);  // change sz
    if (was_closed) {
      running = false;
      break;
    }

    receiverProtocol.handleReceive(state);

  }
}