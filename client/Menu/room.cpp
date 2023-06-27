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
  ui->map->setText(QString("Map: ") + map);
  ui->difficulty->setText(QString("Difficulty: ") + difficulty);
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
