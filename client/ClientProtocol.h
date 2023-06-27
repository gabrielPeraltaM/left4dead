//
// Created by ignacio on 6/23/23.
//

#ifndef LEFT4DEAD_CLIENTPROTOCOL_H
#define LEFT4DEAD_CLIENTPROTOCOL_H

#include <cstdint>
#include <string>

#include "common_src/socket.h"

class ClientProtocol {
 private:
  Socket &socket;
  bool &was_closed;
  bool host = false;
  uint8_t mapSelected = 0;
  uint8_t playerSelected = 0;
  uint8_t difficulty = 0;
  uint32_t gameId = 0;
 public:
  ClientProtocol(Socket &socket, bool &was_closed);
  void createGame(std::string &scenarioName);
  void joinGame();
  uint8_t getPlayerId();
  uint32_t getGameId();
  uint8_t getMapSelected();
  uint8_t getPlayerSelected();
  uint8_t getDifficulty();
  void setGameId(uint32_t gameId);
  void sendCharacterType();
  void sendMapSelected();
  void startGame();
  void waitStart();
  bool isHost() const;
  void setMapSelected(uint8_t mapSelected);
  void setPlayerSelected(uint8_t playerSelected);
  void setDifficulty(uint8_t difficulty);
  void sendDifficulty();
};

#endif  // LEFT4DEAD_CLIENTPROTOCOL_H
