
#include <exception>
#include <iostream>
#include "client_src/client/Client.h"
#include <SDL2pp/SDL2pp.hh>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: ./client <host> <port>" << std::endl;
    return 1;
  }
  const char *hostname = argv[1];
  const char *port = argv[2];

  try {
    Client client(hostname, port);
    client.start(2, RESOURCE_PATH "/backgrounds/War1/Pale/War.png");
    return 0;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}