#ifndef SDL_PRUEBA_RECEIVER_H
#define SDL_PRUEBA_RECEIVER_H

#include <vector>

#include "client/characters/Character.h"
#include "common_src/socket.h"
#include "common_src/thread.h"

class Receiver : public Thread {
 private:
  bool &running;
  std::vector<Character> &characters;
  Socket &socket;

 public:
  Receiver(Socket &socket, bool &was_closed,
           std::vector<Character> &characters);
  void run() override;
};

#endif  // SDL_PRUEBA_RECEIVER_H
