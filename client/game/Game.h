//
// Created by ignacio on 6/9/23.
//

#ifndef SDL_CLIENT_H
#define SDL_CLIENT_H

#include <SDL2pp/SDL2pp.hh>

#include "GameRenderer/GameRenderer.h"
#include "client/characters/Character.h"
#include "client/game/GameProtocol/Receiver.h"
#include "client/game/GameProtocol/Sender.h"
#include "common_src/socket.h"
#include <map>
#include <memory>

using namespace SDL2pp;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

class Game {

    // SDL Variables
    Window window = Window("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                           SCREEN_WIDTH, SCREEN_HEIGHT,
                           SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
    Renderer renderer = Renderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Game Variables
    Socket &socket;
    const int playerId;
    const int numPlayers;
    bool running = true;

    // Storage
    std::map<int, std::shared_ptr<Character>> characters;
    Mix_Music *music = nullptr;

    // Threads
    GameRenderer gameRenderer = GameRenderer(renderer, running, characters, playerId);
    Receiver receiver = Receiver(socket, running, characters);
    Sender sender = Sender(socket, running);

public:
    Game(Socket &socket, int playerId, int numPlayers);

    void start();

    ~Game();
};


#endif //SDL_CLIENT_H
