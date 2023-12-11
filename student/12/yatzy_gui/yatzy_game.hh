#ifndef YATZY_GAME_HH
#define YATZY_GAME_HH

#include <QDialog>

#include "gameengine.hh"

#include <QLabel>

namespace Ui {
  class yatzy_game;
}

class yatzy_game: public QDialog {
  Q_OBJECT

  public:
    explicit yatzy_game(QWidget * parent = nullptr, unsigned int num_players = 1);
  void updateLabelImage(QLabel * label, int value);
  void animateDiceRoll(QLabel* diceLabel,int dice);
  QPixmap getDiceImage(int value);

  ~yatzy_game();
  void update_display();

  QTimer * timer;
  void updateTimerDisplay();

  private slots:

    void on_Roll_button_clicked();

  void on_give_turn_button_clicked();

  void on_Quit_button_clicked();

  void on_resetButton_clicked();

  void on_checkBox_stateChanged(int arg1);

  void on_checkBox_2_stateChanged(int arg1);

  void on_checkBox_5_stateChanged(int arg1);

  void on_checkBox_3_stateChanged(int arg1);

  void on_checkBox_4_stateChanged(int arg1);

  void on_Pause_button_clicked();

  void on_unPause_button_clicked();

  private:
    Ui::yatzy_game * ui;
  GameEngine eng;
  unsigned int player_amount;
  int currentSeconds;
};

#endif // YATZY_GAME_HH
