#ifndef SDL_PRUEBA_RECEIVER_H
#define SDL_PRUEBA_RECEIVER_H

#include <vector>

#include "ReceiverProtocol.h"
#include "client/characters/Character.h"
#include "common_src/socket.h"
#include "common_src/thread.h"

class Receiver : public Thread {
 private:
  bool &running;
  std::map<int, std::shared_ptr<Character>> &characters;
  Socket &socket;
  ReceiverProtocol receiverProtocol = ReceiverProtocol(characters);

 public:
  Receiver(Socket &socket, bool &was_closed,
           std::map<int, std::shared_ptr<Character>> &characters);
  void run() override;
};

#endif  // SDL_PRUEBA_RECEIVER_H
