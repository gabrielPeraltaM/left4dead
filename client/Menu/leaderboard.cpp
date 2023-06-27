#include "leaderboard.h"
#include "ui_leaderboard.h"

LeaderBoard::LeaderBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderBoard)
{
    ui->setupUi(this);
}

LeaderBoard::~LeaderBoard()
{
    delete ui;
}
