#ifndef YATZY_GAME_HH
#define YATZY_GAME_HH

#include <QDialog>
#include "gameengine.hh"

namespace Ui {
class yatzy_game;
}

class yatzy_game : public QDialog
{
    Q_OBJECT

public:
    explicit yatzy_game(QWidget *parent = nullptr,  const GameEngine &eng = GameEngine());
    ~yatzy_game();
    void update_display(const GameEngine &eng);

private slots:
    void on_Quit_clicked();

private:
    Ui::yatzy_game *ui;
};

#endif // YATZY_GAME_HH
