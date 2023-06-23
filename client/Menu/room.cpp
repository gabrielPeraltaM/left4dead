#include "room.h"

#include <iostream>

#include "ui_room.h"

Room::Room(ClientProtocol &protocol, QWidget *parent, QString id)
    : QDialog(parent), ui(new Ui::Room), id(id), protocol(protocol) {
  ui->setupUi(this);
  ui->title->setText(QString("Room ") + id);

  ui->title->repaint();
  if (!protocol.isHost()) {
    ui->Start->setText("Ready");
  }
  ui->MapType->setId(ui->MapType->buttons()[0], 0);
  ui->MapType->setId(ui->MapType->buttons()[1], 1);
  ui->MapType->setId(ui->MapType->buttons()[2], 2);
  ui->PlayerType->setId(ui->PlayerType->buttons()[0], 0);
  ui->PlayerType->setId(ui->PlayerType->buttons()[1], 1);
  ui->PlayerType->setId(ui->PlayerType->buttons()[2], 2);
}

void Room::on_MapType_clicked() {
  protocol.setMapSelected(ui->MapType->checkedId());
}

Room::~Room() { delete ui; }

void Room::on_PlayerType_clicked() {
  protocol.setPlayerSelected(ui->PlayerType->checkedId());
}
