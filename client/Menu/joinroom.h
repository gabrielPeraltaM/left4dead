#ifndef JOINROOM_H
#define JOINROOM_H

#include <QDialog>

namespace Ui {
class JoinRoom;
}

class JoinRoom : public QDialog
{
    Q_OBJECT

public:
    explicit JoinRoom(QWidget *parent = nullptr);
    ~JoinRoom();
    QString getId();

private:
    Ui::JoinRoom *ui;
};

#endif // JOINROOM_H
