#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>
#include "layout/game/Game.h"

using namespace SDL2pp;

int main() try {
    Game game;
    game.StartGame();
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
