#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "common_src/socket.h"

enum OPCODES : uint8_t {
  CREATE = 0x01,
  JOIN = 0x02,
  BROADCAST = 0x03,
  SERVER_BROADCAST = 0x04,
  MOVE = 0x05,
  SHOOT = 0x06,
  ATTACK = 0x07,
  SERVER_MOVE = 0x08,
  SERVER_SHOOT = 0x09,
  SERVER_ATTACK = 0x0A,
};

class Protocol {
 private:
  Socket peer;
 public:
  Protocol(const char *hostname, const char *port);
  ~Protocol() = default;
  // - create: 0x01 <scenario len> <scenario name>
  uint32_t create(uint16_t scenario_len, const char *scenario_name,
                  bool *was_closed);
  // - join: 0x02 <code>
  uint8_t join(uint32_t code, bool *was_closed);
  // - leave
  void leave(bool *was_closed);
};

#endif  // PROTOCOL_H
