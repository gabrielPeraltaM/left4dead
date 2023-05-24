//
// Created by ignacio on 5/24/23.
//

#ifndef LEFT4DEAD_CHARACTER_H
#define LEFT4DEAD_CHARACTER_H

#include <cstdint>
#include <string>

enum class State {
    IDLE, WALK, RUN, ATTACK, HURT, DEAD,
};

class Character {
protected:
    State state = State::IDLE;
    std::string spritePath;
    uint16_t positionX;
    uint16_t positionY;
    uint16_t width;
    uint16_t height;
    uint8_t health;
    uint8_t speed;
    uint8_t damage;
    uint8_t attackSpeed;
    uint8_t attackRange;
    uint8_t attackCooldown;
public:
    Character(uint16_t positionX, uint16_t positionY, uint8_t health, uint8_t speed, uint8_t damage,
              uint8_t attackSpeed, uint8_t attackRange, uint8_t attackCooldown, uint16_t width, uint16_t height, const char *spritePath);

    uint16_t getWidth() const;

    uint16_t getHeight() const;

    uint16_t getPositionX() const;

    uint16_t getPositionY() const;

    State getState() const;

    void setState(State newState);

    std::string getSpritePath() const;

    bool moveX(int16_t x);

    bool moveY(int16_t y);

    bool moveUp();

    bool moveDown();

    bool moveLeft();

    bool moveRight();

    uint8_t getHealth() const;

    void reduceHealth(uint8_t damage);

    uint8_t getSpeed() const;

    uint8_t getDamage() const;

    uint8_t getAttackSpeed() const;

    uint8_t getAttackRange() const;

    uint8_t getAttackCooldown() const;

    virtual void attack() = 0;

    void move(int16_t posX, int16_t posY);

    virtual void die() = 0;

    virtual void spawn() = 0;

    virtual void update() = 0;

    virtual void destroy() = 0;

    virtual void getCharacterType() = 0;
};


#endif //LEFT4DEAD_CHARACTER_H
