#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "common_src/socket.h"

enum OPCODES : uint8_t {
    MOVE_UP = 0x05,
    MOVE_DOWN = 0X06,
    MOVE_LEFT = 0X07,
    MOVE_RIGHT = 0X08,
    SHOOT = 0x09,
    ATTACK = 0x0A,
    RELOAD = 0X0B
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
  // - receive_status
  std::string receive_status(bool *was_closed);
};

#endif  // PROTOCOL_H
