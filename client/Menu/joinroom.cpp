#include "joinroom.h"

#include "ui_joinroom.h"

JoinRoom::JoinRoom(QWidget *parent) : QDialog(parent), ui(new Ui::JoinRoom) {
  ui->setupUi(this);
  ui->PlayerType->setId(ui->PlayerType->buttons()[0], 0);
  ui->PlayerType->setId(ui->PlayerType->buttons()[1], 1);
  ui->PlayerType->setId(ui->PlayerType->buttons()[2], 2);
}

JoinRoom::~JoinRoom() { delete ui; }

QString JoinRoom::getId() { return ui->id->text(); }
int JoinRoom::getPlayerType() { return ui->PlayerType->checkedId(); }
