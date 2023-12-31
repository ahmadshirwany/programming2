#include "mainwindow.hh"

#include "ui_mainwindow.h"

#include <string>

#include "gameengine.hh"

#include "yatzy_game.hh"

#include "error.hh"


MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {
  ui -> setupUi(this);

}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_Enter_clicked() {
  QString lineEditText = ui -> lineEdit -> text();
  std::string player_amount_str = lineEditText.toStdString();
  if (player_amount_str == "") {
    Error_window = new error(this, "Please enter a valid number for the players.");
    Error_window -> show();
    return;
  }
  unsigned int player_amount = 0;
  if (player_amount_str.size() == 1 and isdigit(player_amount_str.at(0))) {
    player_amount = stoi(player_amount_str);
  } else {
    if (!isdigit(player_amount_str.at(0))) {
      Error_window = new error(this, "Please enter a valid number for the players.");
      Error_window -> show();
      return;
    }
    //set_players(eng); // recursive call
    if (player_amount_str.size() != 1) {
      Error_window = new error(this, "Please enter a single-digit number for the players.");
      Error_window -> show();
      return;
    }

  }

  this -> close();
  Yatzy = new yatzy_game(this, player_amount);
  Yatzy -> show();

}

void MainWindow::on_pushButton_clicked() {
  this -> close();
}
