#include "mainwindow.h"

#include <iostream>
#include <string>

#include "./ui_mainwindow.h"
#include "createroom.h"
#include "joinroom.h"
#include "leaderboard.h"
#include "options.h"

MainWindow::MainWindow(ClientProtocol protocol, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), protocol(protocol) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_CreateButton_clicked() {
  CreateRoom create;
  create.setModal(true);
  if (create.exec() == QDialog::Accepted) {
    // Game Name
    std::string name = create.getName().toStdString();
    if (name == "") {
      return;
    }
    // Player Type
    int playerType = create.getPlayerType();
    protocol.setPlayerSelected(playerType);

    // Map
    int map = create.getMap();
    protocol.setMapSelected(map);

    // Difficulty
    int difficulty = create.getDifficulty();
    protocol.setDifficulty(difficulty);

    protocol.createGame(name);

    hide();
    room = new Room(protocol);
    room->setModal(true);
    auto res = room->exec();
    if (res == QDialog::Rejected) {
      show();
    } else if (res == QDialog::Accepted) {
      protocol.startGame();
      close();
      // Exit the app
      QApplication::exit(0);
    }
  }
}

void MainWindow::on_JoinButton_clicked() {
  JoinRoom join;
  join.setModal(true);
  if (join.exec() == QDialog::Accepted) {
    hide();

    int playerType = join.getPlayerType();
    protocol.setPlayerSelected(playerType);

    QString id = join.getId();
    std::string idStd = id.toStdString();
    protocol.setGameId(std::stoi(idStd));
    try {
      protocol.joinGame();
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
      return;
    }

    hide();
    room = new Room(protocol, this);
    room->setModal(true);
    auto res = room->exec();
    if (res == QDialog::Rejected) {
      show();
    } else if (res == QDialog::Accepted) {
      protocol.waitStart();
      close();
      QApplication::exit(0);
    }
  }
}

void MainWindow::on_LeaderBoardButton_clicked() {
  LeaderBoard leaderBoard;
  leaderBoard.setModal(true);
  leaderBoard.exec();
}

void MainWindow::on_pushButton_clicked() {
  Options options;
  options.setModal(true);
  options.exec();
}
