#include "room.h"
#include "ui_room.h"

Room::Room(QWidget *parent, QString id) :
    QDialog(parent),
    ui(new Ui::Room),
    id(id)
{
    ui->setupUi(this);
    ui->title->setText(QString("Room ") + id);
    ui->title->repaint();
}

Room::~Room()
{
    delete ui;
}
