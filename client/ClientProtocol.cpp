//
// Created by ignacio on 6/23/23.
//

#include "ClientProtocol.h"

#include <netinet/in.h>

#include <QApplication>
#include <stdexcept>
#include <string>

#include "client/game/Game.h"
#include "common_src/socket.h"

#define CREATE 0X01
#define JOIN 0X02
#define START 0X03
#define MAP_SELECTED 0X04
#define PLAYER_SELECTED 0X05

ClientProtocol::ClientProtocol(Socket &socket, bool &was_closed)
    : socket(socket), was_closed(was_closed) {}

uint32_t ClientProtocol::createGame(std::string &scenarioName) {
  // Variables
  uint8_t opcode = CREATE;
  uint16_t scenarioNameLength = scenarioName.length();
  uint16_t scenarioNameLengthNetwork = htons(scenarioNameLength);
  uint32_t gameId;

  // Send opcode
  socket.sendall(&opcode, 1, &was_closed);
  // Send scenario name length
  socket.sendall(&scenarioNameLengthNetwork, 4, &was_closed);
  // Send scenario name
  socket.sendall(scenarioName.c_str(), scenarioNameLength, &was_closed);

  socket.recvall(&gameId, 4, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");

  host = true;
  return ntohl(gameId);
}

uint8_t ClientProtocol::joinGame(uint32_t gameId) {
  // Variables
  uint8_t opcode = JOIN;
  uint32_t gameIdNetwork = htonl(gameId);
  uint8_t response;

  // Send opcode
  socket.sendall(&opcode, 1, &was_closed);
  // Send game id
  socket.sendall(&gameIdNetwork, 4, &was_closed);

  socket.recvall(&response, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");
  return response;
}

uint8_t ClientProtocol::getPlayerId() {
  uint8_t playerId;

  socket.recvall(&playerId, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");
  return playerId;
}

void ClientProtocol::startGame() {
  uint8_t opcode = START;

  if (host) {
    socket.sendall(&opcode, 1, &was_closed);
    if (was_closed) throw std::runtime_error("Connection closed");
  }
  waitStart();
}

void ClientProtocol::sendCharacterType() {
  uint8_t opcode = PLAYER_SELECTED;
  socket.sendall(&opcode, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");

  socket.sendall(&playerSelected, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");
}

void ClientProtocol::sendMapSelected() {
  uint8_t opcode = MAP_SELECTED;

  socket.sendall(&opcode, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");

  socket.sendall(&mapSelected, 1, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");
}

void ClientProtocol::waitStart() {
  uint8_t playerId = getPlayerId();
  uint16_t numPlayers;
  uint16_t numZombies;

  socket.recvall(&numPlayers, 2, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");

  numPlayers = ntohs(numPlayers);
  std::cout << "numPlayers: " << numPlayers << std::endl;

  socket.recvall(&numZombies, 2, &was_closed);
  if (was_closed) throw std::runtime_error("Connection closed");

  numZombies = ntohs(numZombies);
  std::cout << "numZombies: " << numZombies << std::endl;

  Game game(socket, playerId, numPlayers, mapSelected, numZombies);
  game.start();
}

bool ClientProtocol::isHost() const { return host; }

void ClientProtocol::setMapSelected(uint8_t map) { mapSelected = map; }

void ClientProtocol::setPlayerSelected(uint8_t player) {
  playerSelected = player;
}
void ClientProtocol::setGameId(uint32_t gameId) { this->gameId = gameId; }
uint32_t ClientProtocol::getGameId() { return gameId; }
uint8_t ClientProtocol::getMapSelected() { return mapSelected; }
uint8_t ClientProtocol::getPlayerSelected() { return playerSelected; }
uint8_t ClientProtocol::getDifficulty() { return difficulty; }
void ClientProtocol::setDifficulty(uint8_t difficulty) {
  this->difficulty = difficulty;
}
