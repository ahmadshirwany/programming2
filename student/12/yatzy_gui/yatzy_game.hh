#ifndef YATZY_GAME_HH
#define YATZY_GAME_HH

#include <QDialog>

#include "gameengine.hh"

namespace Ui {
  class yatzy_game;
}

class yatzy_game: public QDialog {
  Q_OBJECT

  public:
    explicit yatzy_game(QWidget * parent = nullptr, unsigned int num_players = 1);
  ~yatzy_game();
  void update_display();
  QTimer* timer;
  void updateTimerDisplay();

  private slots:
    void on_Quit_clicked();

  void on_Roll_button_clicked();

  void on_give_turn_button_clicked();

  void on_Quit_button_clicked();

  void on_resetButton_clicked();

  private:
    Ui::yatzy_game * ui;
  GameEngine eng;
  unsigned int player_amount;
  int currentSeconds;
};

#endif // YATZY_GAME_HH
