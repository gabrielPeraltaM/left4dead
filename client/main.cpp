#include "game/Game.h"
#include "Client.h"

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./client <host> <port>" << std::endl;
        return 1;
    }

    const char *hostname = argv[1];
    const char *port = argv[2];

    Client client(hostname, port);
    client.run();

    return 0;
}
