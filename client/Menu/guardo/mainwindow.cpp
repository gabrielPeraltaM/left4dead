#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "client/ClientProtocol.h"

MainWindow::MainWindow(ClientProtocol protocol, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), protocol(protocol) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

// CREATE
void MainWindow::on_CreateButton_clicked() {
  CreateRoom create;
  create.setModal(true);
  if (create.exec() == QDialog::Accepted) {
    std::string name = create.getName().toStdString();
    uint32_t gameId = protocol.createGame(name);
    hide();
    room = new Room(protocol, this, QString::number(gameId));
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

// JOIN
void MainWindow::on_JoinButton_clicked() {
  JoinRoom join;
  join.setModal(true);
  if (join.exec() == QDialog::Accepted) {
    std::string id = join.getId().toStdString();
    uint32_t gameId = std::stoi(id);
    uint8_t response = protocol.joinGame(gameId);

    if (response == 1) {
      return;
    }

    hide();
    room = new Room(protocol, this, QString::number(gameId));
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
