#include "createroom.h"

#include "ui_createroom.h"

CreateRoom::CreateRoom(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateRoom) {
  ui->setupUi(this);
        ui->playerType->setId(ui->playerType->buttons()[0], 1);
        ui->playerType->setId(ui->playerType->buttons()[1], 3);
        ui->playerType->setId(ui->playerType->buttons()[2], 2);

        ui->difficulty->setId(ui->difficulty->buttons()[0], 0);
        ui->difficulty->setId(ui->difficulty->buttons()[1], 1);
        ui->difficulty->setId(ui->difficulty->buttons()[2], 2);

        ui->map->setId(ui->map->buttons()[0], 0);
        ui->map->setId(ui->map->buttons()[1], 1);
        ui->map->setId(ui->map->buttons()[2], 2);
}

CreateRoom::~CreateRoom() { delete ui; }

QString CreateRoom::getName() { return ui->name->displayText(); }
int CreateRoom::getPlayerType() { return ui->playerType->checkedId(); }
int CreateRoom::getDifficulty() { return ui->difficulty->checkedId(); }
int CreateRoom::getMap() { return ui->map->checkedId(); }
