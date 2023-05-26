//
// Created by ignacio on 5/25/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_menu.h" resolved

#include "menu.h"
#include "ui_menu.h"


menu::menu(QWidget *parent) :
        QWidget(parent), ui(new Ui::menu) {
    ui->setupUi(this);
}

menu::~menu() {
    delete ui;
}
