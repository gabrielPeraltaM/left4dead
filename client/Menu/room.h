#ifndef ROOM_H
#define ROOM_H

#include <QDialog>

namespace Ui {
class Room;
}

class Room : public QDialog
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = nullptr, QString id = 0);
    ~Room();

private:
    Ui::Room *ui;
    QString id;
};

#endif // ROOM_H
