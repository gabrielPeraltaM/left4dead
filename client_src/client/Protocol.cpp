#include "Protocol.h"

#include <netinet/in.h>

#include <iostream>
#include <sstream>

Protocol::Protocol(const char *hostname, const char *port)
    : peer(hostname, port) {}

uint32_t Protocol::create(uint16_t scenario_len, const char *scenario_name,
                          bool *was_closed) {
  // Send opcode
  const uint8_t opcode = CREATE;
  peer.sendall(&opcode, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send scenario len
  uint16_t scenario_len_n = htons(scenario_len);
  peer.sendall(&scenario_len_n, 2, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send scenario name
  peer.sendall(scenario_name, scenario_len, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Receive response
  uint32_t response;
  peer.recvall(&response, 4, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
  return ntohl(response);
}

uint8_t Protocol::join(uint32_t code, bool *was_closed) {
  // Send opcode
  const uint8_t opcode = JOIN;
  peer.sendall(&opcode, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send code
  uint32_t code_n = htonl(code);
  peer.sendall(&code_n, 4, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Receive response
  uint8_t response;
  peer.recvall(&response, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
  return response;
}

void Protocol::broadcast(uint16_t msg_len, const char *msg, bool *was_closed) {
  // Send opcode
  const uint8_t opcode = BROADCAST;
  peer.sendall(&opcode, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send msg_len
  uint16_t msg_len_n = htons(msg_len);
  peer.sendall(&msg_len_n, 2, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send msg
  peer.sendall(msg, msg_len, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
}

std::string Protocol::read_one(bool *was_closed) {
  char buf[256];

  // Read opcode
  peer.recvall(buf, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
  uint8_t opcode = buf[0];
  if (opcode != SERVER_BROADCAST) throw std::runtime_error("Invalid opcode");

  // Read msg_len
  peer.recvall(buf, 2, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
  uint16_t msg_len = ntohs(*reinterpret_cast<uint16_t *>(buf));

  // Read msg
  peer.recvall(buf, msg_len, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
  std::string msg = std::string(buf, msg_len);
  return msg;
}

void Protocol::leave(bool *was_closed) {
  peer.shutdown(SHUT_RDWR);
  peer.close();
  *was_closed = true;
}
void Protocol::move(uint8_t player_id, int8_t directionX, int8_t directionY,
                    bool *was_closed) {
  // Send opcode
  const uint8_t opcode = MOVE;
  peer.sendall(&opcode, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send player_id
  peer.sendall(&player_id, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send directionX
  peer.sendall(&directionX, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send directionY
  peer.sendall(&directionY, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
}
void Protocol::shoot(uint8_t player_id, int8_t directionX, int8_t directionY,
                     bool *was_closed) {
  // Send opcode
  const uint8_t opcode = SHOOT;
  peer.sendall(&opcode, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send player_id
  peer.sendall(&player_id, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send directionX
  peer.sendall(&directionX, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");

  // Send directionY
  peer.sendall(&directionY, 1, was_closed);
  if (*was_closed) throw std::runtime_error("Connection closed");
}
