#include "yatzy_game.hh"
#include "ui_yatzy_game.h"
#include "gameengine.hh"
#include "string"

yatzy_game::yatzy_game(QWidget *parent,const GameEngine &eng) :
    QDialog(parent),
    ui(new Ui::yatzy_game)
{
    ui->setupUi(this);
    QPixmap diceImage(":/new/prefix1/1.png");
    ui->label->setPixmap(diceImage);
    QPixmap diceImage2(":/new/prefix1/2.png");
    ui->label_2->setPixmap(diceImage2);
    QPixmap diceImage3(":/new/prefix1/3.png");
    ui->label_3->setPixmap(diceImage3);
    QPixmap diceImage4(":/new/prefix1/4.png");
    ui->label_4->setPixmap(diceImage4);
    QPixmap diceImage5(":/new/prefix1/5.png");
    ui->label_5->setPixmap(diceImage5);
    QPixmap diceImage6(":/new/prefix1/6.png");
    ui->label_6->setPixmap(diceImage6);
    update_display(eng);



}

yatzy_game::~yatzy_game()
{
    delete ui;
}

void yatzy_game::on_Quit_clicked()
{
    this->close();
}
void yatzy_game::update_display(const GameEngine &eng){
    unsigned int playerno = eng.report_player_status_Gui();
    ui->label_10->setText(QString::number(playerno));
    unsigned int turn_left = eng.report_turn_left_Gui();
    ui->label_13->setText(QString::number(turn_left));
}
