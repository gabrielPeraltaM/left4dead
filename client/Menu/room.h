#ifndef ROOM_H
#define ROOM_H

#include <QDialog>

#include "client/ClientProtocol.h"

namespace Ui {
class Room;
}

class Room : public QDialog
{
    Q_OBJECT

public:
    explicit Room(ClientProtocol &protocol, QWidget *parent = nullptr);
    ~Room();

private:
    Ui::Room *ui;
    QString id;
    QString map;
    QString difficulty;
    QString playerType;
    ClientProtocol &protocol;
};

#endif // ROOM_H
