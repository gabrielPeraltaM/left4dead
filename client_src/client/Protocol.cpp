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

void Protocol::leave(bool *was_closed) {
  peer.shutdown(SHUT_RDWR);
  peer.close();
  *was_closed = true;
}
