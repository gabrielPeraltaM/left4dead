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
    const int numZombies;
    const int mapSelected;
    bool isLoadingPlayers = true;
    bool running = true; // std atomic bool
    bool muted = false;
    uint8_t gameStatus = 0;

    // Storage
    //std::map<int, std::shared_ptr<Character>> characters;
    StateQueue states;

    // Music
    Mix_Music *music = nullptr;
    int musicIndex = 0;

    // Threads
    GameRenderer gameRenderer = GameRenderer(renderer, running, playerId, mapSelected,
                                             isLoadingPlayers, gameStatus, states,
                                             numZombies + numPlayers);
    Receiver receiver = Receiver(socket, running,
                                 numZombies+numPlayers,
                                 isLoadingPlayers, playerId, gameStatus, states);
    Sender sender = Sender(socket, running);

public:
    Game(Socket &socket, int playerId, int numPlayers, int mapSelected, int numZombies);

    void start();

    ~Game();
};


#endif //SDL_CLIENT_H
