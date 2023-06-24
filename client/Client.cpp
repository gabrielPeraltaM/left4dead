//
// Created by ignacio on 6/10/23.
//

#include "Client.h"

#include <netinet/in.h>

#include <QApplication>
#include <sstream>
#include <string>

#include "client/ClientProtocol.h"
#include "client/Menu/mainwindow.h"
#include "client/game/Game.h"


Client::Client(const char *hostname, const char *port) : peer(hostname, port) {}

void Client::run() {
  int argc = 1;
  char *argv[] = {(char *)"./client"};
  QApplication app(argc, argv);
  MainWindow window(ClientProtocol(peer, was_closed));
  window.show();
  app.exec();
}
