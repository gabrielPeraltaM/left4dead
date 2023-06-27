#include "room.h"

#include <string>

#include "ui_room.h"

Room::Room(ClientProtocol &protocol, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Room),
      protocol(protocol),
      id(""),
      map(""),
      difficulty(""),
      playerType("") {
  ui->setupUi(this);
  id = std::to_string(protocol.getGameId()).c_str();
  map = std::to_string(protocol.getMapSelected()).c_str();
  difficulty = std::to_string(protocol.getDifficulty()).c_str();
  playerType = std::to_string(protocol.getPlayerSelected()).c_str();

  ui->title->setText(QString("Room ") + id);
  if (map == "0")
    map = "Sabana";
  else if (map == "1")
    map = "City";
  else if (map == "2")
    map = "Dark";
  ui->map->setText(QString("Map: ") + map);

  if(difficulty == "0")
    difficulty = "Easy";
  else if(difficulty == "1")
    difficulty = "Medium";
  else if(difficulty == "2")
    difficulty = "Hard";
  ui->difficulty->setText(QString("Difficulty: ") + difficulty);

  if (playerType == "1")
    playerType = "IDF";
  else if (playerType == "2")
    playerType = "Scout";
  else if (playerType == "3")
    playerType = "P90";

  ui->playerType->setText(QString("Player Type: ") + playerType);
  ui->title->repaint();
  ui->map->repaint();
  ui->difficulty->repaint();
  ui->playerType->repaint();

  if (!protocol.isHost()) {
    ui->Start->setText("Ready");
  }
}

Room::~Room() { delete ui; }
