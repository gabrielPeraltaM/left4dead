#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int main() try {
	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Create main window
	Window window("Game",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
            SDL_WINDOW_MAXIMIZED);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Change background color to red
    renderer.SetDrawColor(255,0,0,255);

    // Obtengo el centro de la pantall
    int centerY = renderer.GetOutputHeight()/2;
    int centerX = renderer.GetOutputWidth()/2;

	// Load player image as a new texture
	Texture player(renderer, RESOURCE_PATH "/Soldier_1/Idle.png");

	// Clear screen
	renderer.Clear();

	// Render our image
	renderer.Copy(player,
                  Rect(30, 30, 100, 100),
                  Rect(centerX, centerY, 100, 100));

	// Show rendered frame
	renderer.Present();

	// 5 second delay
	SDL_Delay(5000);

	// Here all resources are automatically released and library deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
