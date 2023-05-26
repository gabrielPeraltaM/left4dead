//
// Created by ignacio on 5/25/23.
//

#ifndef LEFT4DEAD_MENU_H
#define LEFT4DEAD_MENU_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QWidget {
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);

    ~menu() override;

private:
    Ui::menu *ui;
};


#endif //LEFT4DEAD_MENU_H
