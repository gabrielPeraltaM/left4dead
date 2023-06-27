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

  // Set default MapType the first one
  ui->MapType->button(0)->setChecked(true);
  // Set default PlayerType the first one
  ui->PlayerType->button(0)->setChecked(true);

  connect(ui->MapType, SIGNAL(idClicked(int)), this,
          SLOT(onMapSelected(int)));
  connect(ui->PlayerType, SIGNAL(idClicked(int)), this,
          SLOT(onPlayerSelected(int)));
}

void Room::onMapSelected(int mapId) { protocol.setMapSelected(mapId); }

void Room::onPlayerSelected(int playerType) {
  protocol.setPlayerSelected(playerType);
}

Room::~Room() { delete ui; }
