#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QDialog>

namespace Ui {
class CreateRoom;
}

class CreateRoom : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRoom(QWidget *parent = nullptr);
    ~CreateRoom();
    QString getName();
    int getPlayerType();
    int getDifficulty();
    int getMap();

private:
    Ui::CreateRoom *ui;
};

#endif // CREATEROOM_H
