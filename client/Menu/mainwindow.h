#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "client/ClientProtocol.h"
#include "room.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ClientProtocol clientProtocol, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CreateButton_clicked();

    void on_JoinButton_clicked();

private:
    Ui::MainWindow *ui;
    Room *room;
    ClientProtocol protocol;
};
#endif // MAINWINDOW_H
