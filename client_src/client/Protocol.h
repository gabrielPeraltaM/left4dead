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
  RELOAD = 0X0B,
  HURT = 0X0C,
  RUN_UP = 0X0D,
  RUN_DOWN = 0X0E,
  RUN_LEFT = 0X0F,
  RUN_RIGHT = 0x10
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
  // - receive_player
  int receive_player(bool *was_closed);
  // - receive_action
  uint8_t receive_action(bool *was_closed);

  // - moveUp
  void moveUp(bool *was_closed);

  // - moveDown
  void moveDown(bool *was_closed);

  // - moveLeft
  void moveLeft(bool *was_closed);

  // - moveRight
  void moveRight(bool *was_closed);

  // - shoot
  void shoot(bool *was_closed);

  // - attack
  void attack(bool *was_closed);

  // - reload
  void reload(bool *was_closed);
};

#endif  // PROTOCOL_H
