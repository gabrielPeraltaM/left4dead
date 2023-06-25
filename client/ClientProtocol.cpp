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

void ClientProtocol::sendCharacterType(uint8_t characterType) {
  uint8_t opcode = characterType;

  socket.sendall(&opcode, 1, &was_closed);
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

void ClientProtocol::setMapSelected(int map) { mapSelected = map; }

void ClientProtocol::setPlayerSelected(int player) { playerSelected = player; }
