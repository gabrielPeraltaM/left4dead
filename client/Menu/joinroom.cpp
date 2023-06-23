#include "joinroom.h"
#include "ui_joinroom.h"

JoinRoom::JoinRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinRoom)
{
    ui->setupUi(this);
}

JoinRoom::~JoinRoom()
{
    delete ui;
}

QString JoinRoom::getId()
{
    return ui->id->text();
}
