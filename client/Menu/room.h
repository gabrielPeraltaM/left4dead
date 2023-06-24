#ifndef ROOM_H
#define ROOM_H

#include <QDialog>

#include "client/ClientProtocol.h"

namespace Ui {
class Room;
}

class Room : public QDialog {
  Q_OBJECT

 public:
  explicit Room(ClientProtocol &protocol, QWidget *parent = nullptr,
                QString id = nullptr);
  ~Room();

 private slots:
  void onMapSelected(int id);
  void onPlayerSelected(int id);

 private:
  Ui::Room *ui;
  QString id;
  ClientProtocol &protocol;
};

#endif  // ROOM_H
