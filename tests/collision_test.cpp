//
// Created by gabriel on 30/06/23.
//

#include "gtest/gtest.h"
#include "../server_src/game/Idf.h"
#include "../server_src/game/P90.h"
#include "../server_src/game/Scout.h"

TEST(collision, characters_collide) {
  int dead_players = 0;
  Character *player1 = new Idf(0, 0, dead_players);
  Character *player2 = new P90(50, 0, dead_players);
  Character *player3 = new Scout(100, 0, dead_players);

  EXPECT_EQ(true, player1->collision(player2, 40, 0));
  EXPECT_EQ(true, player2->collision(player1, 10, 0));
  EXPECT_EQ(true, player2->collision(player3, 90, 0));
  EXPECT_EQ(true, player3->collision(player2, 60, 0));
}

TEST(collision, characters_not_collide) {
  int dead_players = 0;
  Character *player1 = new Idf(0, 50, dead_players);
  Character *player2 = new P90(50, 100, dead_players);
  Character *player3 = new Scout(100, 50, dead_players);

  EXPECT_EQ(false, player1->collision(player2, 40, 50));
  EXPECT_EQ(false, player2->collision(player1, 10, 100));
  EXPECT_EQ(false, player2->collision(player3, 90, 100));
  EXPECT_EQ(false, player3->collision(player2, 60, 50));
}

TEST(collision, vertical_movement_collide) {
  int dead_players = 0;
  Character *player1 = new Idf(50, 0, dead_players);
  Character *player2 = new P90(50, 50, dead_players);
  Character *player3 = new Scout(50, 100, dead_players);

  EXPECT_EQ(true, player1->collision(player2, 50, 40));
  EXPECT_EQ(true, player2->collision(player1, 50, 10));
  EXPECT_EQ(true, player2->collision(player3, 50, 90));
  EXPECT_EQ(true, player3->collision(player2, 50, 60));
}

TEST(collision, vertical_movement_not_collide) {
  int dead_players = 0;
  Character *player1 = new Idf(50, 0, dead_players);
  Character *player2 = new P90(100, 50, dead_players);
  Character *player3 = new Scout(150, 150, dead_players);

  EXPECT_EQ(false, player1->collision(player2, 50, 20));
  EXPECT_EQ(false, player2->collision(player1, 100, 0));
  EXPECT_EQ(false, player2->collision(player3, 100, 150));
  EXPECT_EQ(false, player3->collision(player2, 150, 50));
}
