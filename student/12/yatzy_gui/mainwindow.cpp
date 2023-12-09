#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>
#include "gameengine.hh"
#include "yatzy_game.hh"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Enter_clicked()
{
    QString lineEditText = ui->lineEdit->text();
    std::string player_amount_str = lineEditText.toStdString();
    GameEngine eng;
    unsigned int player_amount = 0;
    if(player_amount_str.size() == 1 and isdigit(player_amount_str.at(0)))
    {
        player_amount = stoi(player_amount_str);
    }
    else
    {
        //set_players(eng); // recursive call
    }
    for(unsigned int i = 0; i < player_amount; ++i)
    {
        Player player = {i + 1, INITIAL_NUMBER_OF_ROLLS, {}, {}};
        eng.add_player(player);
    }

    this->close();
    Yatzy = new yatzy_game(this,eng);
    Yatzy->show();

}


void MainWindow::on_Quit_clicked()
{
    this->close();
}

