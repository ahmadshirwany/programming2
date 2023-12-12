#include "yatzy_game.hh"

#include "ui_yatzy_game.h"

#include "gameengine.hh"

#include "string"

#include <sstream>

#include <QTimer>

#include "functions.hh"

#include <QPropertyAnimation>

#include <QSequentialAnimationGroup>


yatzy_game::yatzy_game(QWidget * parent, unsigned int num_players):
  QDialog(parent),
  ui(new Ui::yatzy_game),
  player_amount(num_players) {
    ui -> setupUi(this);
    timer = new QTimer(this);
    connect(timer, & QTimer::timeout, this, & yatzy_game::updateTimerDisplay);
    connect(ui -> Pause_button, & QPushButton::clicked, this, & yatzy_game::on_Pause_button_clicked);
    for (unsigned int i = 0; i < player_amount; ++i) {
      Player player = {
        i + 1,
        INITIAL_NUMBER_OF_ROLLS,
        {},
        {},
        std::vector < bool > (NUMBER_OF_DICES, false)
      };
      eng.add_player(player);
    }
    timer -> start(1000);
    QPixmap diceImage(":/images/empty.png");
    ui -> label -> setPixmap(diceImage);
    QPixmap diceImage2(":/images/empty.png");
    ui -> label_2 -> setPixmap(diceImage2);
    QPixmap diceImage3(":/images/empty.png");
    ui -> label_3 -> setPixmap(diceImage3);
    QPixmap diceImage4(":/images/empty.png");
    ui -> label_4 -> setPixmap(diceImage4);
    QPixmap diceImage5(":/images/empty.png");
    ui -> label_5 -> setPixmap(diceImage5);
    ui -> unPause_button -> setEnabled(false);
    update_display();
    currentSeconds = 0;
    updateTimerDisplay();

  }

yatzy_game::~yatzy_game() {
  delete ui;
}

void yatzy_game::update_display() {
  unsigned int playerno = eng.report_player_status_Gui();
  ui -> label_10 -> setText(QString::number(playerno));
  unsigned int turn_left = eng.report_turn_left_Gui();
  ui -> label_13 -> setText(QString::number(turn_left));
  ui -> label_17 -> setText(QString::number(3 - turn_left));
  ui -> label_14 -> setText(QString::number(player_amount));
  if (eng.all_turns_used()) {
    std::string winner = eng.report_winner_gui();
    QString text = QString::fromStdString(winner);
    ui -> textEdit -> append(text);
    QTextCursor cursor = ui -> textEdit -> textCursor();
    cursor.movePosition(QTextCursor::End);
    ui -> textEdit -> setTextCursor(cursor);
    ui->Pause_button->setEnabled(false);
  }
  if (turn_left == 0) {
    ui -> Roll_button -> setEnabled(false);
  } else {
    ui -> Roll_button -> setEnabled(true);
  }
  if (eng.is_game_over()) {
    ui -> give_turn_button -> setEnabled(false);
    ui -> Quit_button -> setEnabled(false);
  } else {
    ui -> give_turn_button -> setEnabled(true);
    ui -> Quit_button -> setEnabled(true);
  }
}

void yatzy_game::on_Roll_button_clicked() {
  vector < int > rolledValues = eng.roll_gui();
  string textual_description = "";
  construe_result(eng.players_[eng.game_turn_].latest_point_values_, textual_description);
  QString text = QString::fromStdString(textual_description);
  ui -> textEdit -> append(text);
  QTextCursor cursor = ui -> textEdit -> textCursor();
  cursor.movePosition(QTextCursor::End);
  ui -> textEdit -> setTextCursor(cursor);
  animateDiceRoll(ui -> label, rolledValues[0]);
  animateDiceRoll(ui -> label_2, rolledValues[1]);
  animateDiceRoll(ui -> label_3, rolledValues[2]);
  animateDiceRoll(ui -> label_4, rolledValues[3]);
  animateDiceRoll(ui -> label_5, rolledValues[4]);
  update_display();
}


void yatzy_game::on_give_turn_button_clicked() {
  eng.give_turn();
  update_display();
  const std::vector < bool > & lockedDice = eng.players_[eng.game_turn_].locked_dice;
  ui -> checkBox -> setChecked(lockedDice[0]);
  ui -> checkBox_2 -> setChecked(lockedDice[1]);
  ui -> checkBox_3 -> setChecked(lockedDice[2]);
  ui -> checkBox_4 -> setChecked(lockedDice[3]);
  ui -> checkBox_5 -> setChecked(lockedDice[4]);

}

void yatzy_game::on_Quit_button_clicked() {
  std::string winner = eng.report_winner_gui();
  QString text = QString::fromStdString(winner);
  ui -> textEdit -> append(text);
  QTextCursor cursor = ui -> textEdit -> textCursor();
  cursor.movePosition(QTextCursor::End);
  ui -> textEdit -> setTextCursor(cursor);
  ui -> Roll_button -> setEnabled(false);
  ui -> give_turn_button -> setEnabled(false);
  ui -> Quit_button -> setEnabled(false);
  ui -> Pause_button -> setEnabled(false);
}

void yatzy_game::on_resetButton_clicked() {
  GameEngine newEng;
  eng = newEng;
  for (unsigned int i = 0; i < player_amount; ++i) {
    Player player = {
      i + 1,
      INITIAL_NUMBER_OF_ROLLS,
      {},
      {},
      std::vector < bool > (NUMBER_OF_DICES, false)
    };
    eng.add_player(player);
  }
  ui -> textEdit -> clear();
  update_display();
  currentSeconds = 0;
  updateTimerDisplay();
  ui -> checkBox -> setChecked(false);
  ui -> checkBox_2 -> setChecked(false);
  ui -> checkBox_3 -> setChecked(false);
  ui -> checkBox_4 -> setChecked(false);
  ui -> checkBox_5 -> setChecked(false);
  ui -> unPause_button -> setEnabled(false);
  ui -> Pause_button -> setEnabled(true);
  animateDiceRoll(ui -> label, 0);
  animateDiceRoll(ui -> label_2, 0);
  animateDiceRoll(ui -> label_3, 0);
  animateDiceRoll(ui -> label_4, 0);
  animateDiceRoll(ui -> label_5, 0);

}

void yatzy_game::updateTimerDisplay() {
  // Update the current time on the display
  currentSeconds++;
  int min = currentSeconds / 60;
  int sec = currentSeconds % 60;
  ui -> lcdNumberSec -> display(sec);
  ui -> lcdNumberMin -> display(min);
}

void yatzy_game::on_checkBox_stateChanged(int state) {
  eng.players_[eng.game_turn_].locked_dice[0] = (state == Qt::Checked);
}

void yatzy_game::on_checkBox_2_stateChanged(int state) {
  eng.players_[eng.game_turn_].locked_dice[1] = (state == Qt::Checked);
}

void yatzy_game::on_checkBox_5_stateChanged(int state) {
  eng.players_[eng.game_turn_].locked_dice[4] = (state == Qt::Checked);
}

void yatzy_game::on_checkBox_3_stateChanged(int state) {
  eng.players_[eng.game_turn_].locked_dice[2] = (state == Qt::Checked);
}

void yatzy_game::on_checkBox_4_stateChanged(int state) {
  eng.players_[eng.game_turn_].locked_dice[3] = (state == Qt::Checked);
}

void yatzy_game::on_Pause_button_clicked() {
  if (timer -> isActive()) {
    timer -> stop();

    // Disable buttons
    ui -> Roll_button -> setEnabled(false);
    ui -> give_turn_button -> setEnabled(false);
    ui -> Quit_button -> setEnabled(false);

    // Disable checkboxes
    ui -> checkBox -> setEnabled(false);
    ui -> checkBox_2 -> setEnabled(false);
    ui -> checkBox_3 -> setEnabled(false);
    ui -> checkBox_4 -> setEnabled(false);
    ui -> checkBox_5 -> setEnabled(false);
    ui -> Pause_button -> setEnabled(false);
    ui -> resetButton -> setEnabled(false);
    ui -> unPause_button -> setEnabled(true);
    ui -> textEdit -> append("Pause");
    QTextCursor cursor = ui -> textEdit -> textCursor();
    cursor.movePosition(QTextCursor::End);
    ui -> textEdit -> setTextCursor(cursor);
    // Add more for checkBox_6 and any additional checkboxes you have

  }
}

void yatzy_game::on_unPause_button_clicked() {
  timer -> start(1000);
  ui -> Roll_button -> setEnabled(true);
  ui -> give_turn_button -> setEnabled(true);
  ui -> Quit_button -> setEnabled(true);

  ui -> checkBox -> setEnabled(true);
  ui -> checkBox_2 -> setEnabled(true);
  ui -> checkBox_3 -> setEnabled(true);
  ui -> checkBox_4 -> setEnabled(true);
  ui -> checkBox_5 -> setEnabled(true);
  ui -> Pause_button -> setEnabled(true);
  ui -> unPause_button -> setEnabled(false);
  ui -> textEdit -> append("Unpause");
  QTextCursor cursor = ui -> textEdit -> textCursor();
  cursor.movePosition(QTextCursor::End);
  ui -> textEdit -> setTextCursor(cursor);
}

void yatzy_game::animateDiceRoll(QLabel * diceLabel, int value) {
  QTimer * timer2 = new QTimer(this);
  QPixmap emptyDice(":/images/empty.png");
  QPixmap dice1(":/images/1.png");
  QPixmap dice2(":/images/2.png");
  QPixmap dice3(":/images/3.png");
  QPixmap dice4(":/images/4.png");
  QPixmap dice5(":/images/5.png");
  QPixmap dice6(":/images/6.png");
  int animationStep = 0;
  const int totalAnimationSteps = 6; // Number of steps in the animation

  connect(timer2, & QTimer::timeout, [ = ]() mutable {
    if (animationStep < totalAnimationSteps) {
      switch (animationStep) {
      case 0:
        diceLabel -> setPixmap(dice1);
        break;
      case 1:
        diceLabel -> setPixmap(dice2);
        break;
      case 2:
        diceLabel -> setPixmap(dice3);
        break;
      case 3:
        diceLabel -> setPixmap(dice4);
        break;
      case 4:
        diceLabel -> setPixmap(dice5);
        break;
      case 5:
        diceLabel -> setPixmap(dice6);
        break;
      }
    } else {
      // Stop the timer after completing the animation
      QString imagePath = QString(":/images/%1.png").arg(value);
      QPixmap diceImage(imagePath);
      diceLabel -> setPixmap(diceImage);
      timer2 -> stop();
      timer2 -> deleteLater();
    }

    animationStep++;
  });

  // Set the timer interval and start it
  timer2 -> start(100);
}
