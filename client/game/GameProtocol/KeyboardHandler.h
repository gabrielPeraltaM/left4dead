//
// Created by ignacio on 6/19/23.
//

#ifndef LEFT4DEAD_KEYBOARDHANDLER_H
#define LEFT4DEAD_KEYBOARDHANDLER_H

#include <cstdint>
#include <map>

class KeyboardHandler {
 private:
  std::map<int, bool> keys;
 public:
  KeyboardHandler();
  void setPressed(int key);
  void setReleased(int key);
  uint8_t getMovement() const;
  int getDirection() const;
  uint8_t getAction() const;
  ~KeyboardHandler() = default;
};

#endif  // LEFT4DEAD_KEYBOARDHANDLER_H
