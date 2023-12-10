#include "yatzy_game.hh"
#include "ui_yatzy_game.h"
#include "gameengine.hh"
#include "string"
#include <sstream>

yatzy_game::yatzy_game(QWidget *parent,unsigned int num_players) :
    QDialog(parent),
    ui(new Ui::yatzy_game),
     player_amount(num_players)
{
    for(unsigned int i = 0; i < player_amount; ++i)
    {
        Player player = {i + 1, INITIAL_NUMBER_OF_ROLLS, {}, {}};
        eng.add_player(player);
    }
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
    update_display();



}

yatzy_game::~yatzy_game()
{
    delete ui;
}

void yatzy_game::on_Quit_clicked()
{
    this->close();
}
void yatzy_game::update_display(){
    unsigned int playerno = eng.report_player_status_Gui();
    ui->label_10->setText(QString::number(playerno));
    unsigned int turn_left = eng.report_turn_left_Gui();
    ui->label_13->setText(QString::number(turn_left));
    ui->label_14->setText(QString::number(player_amount));
    if (turn_left==0){
           ui->Roll_button->setEnabled(false);
    }
    else{
        ui->Roll_button->setEnabled(true);
    }
    if(eng.all_turns_used()){
        std::string winner = eng.report_winner_gui();
        QString text = QString::fromStdString(winner);
        ui->textEdit->append(text);
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);
    }
}

void yatzy_game::on_Roll_button_clicked()
{
   std::ostringstream st = eng.roll_gui();
   QString text = QString::fromStdString(st.str());
   ui->textEdit->append(text);
   QTextCursor cursor = ui->textEdit->textCursor();
   cursor.movePosition(QTextCursor::End);
   ui->textEdit->setTextCursor(cursor);
    update_display();

}


void yatzy_game::on_give_turn_button_clicked()
{
    eng.give_turn();
    update_display();
}


void yatzy_game::on_Quit_button_clicked()
{
    std::string winner = eng.report_winner_gui();
    QString text = QString::fromStdString(winner);
    ui->textEdit->append(text);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    ui->Roll_button->setEnabled(false);
    ui->give_turn_button->setEnabled(false);
    ui->Quit_button->setEnabled(false);
}


void yatzy_game::on_resetButton_clicked()
{
    GameEngine newEng;
    eng = newEng;
    for(unsigned int i = 0; i < player_amount; ++i)
    {
        Player player = {i + 1, INITIAL_NUMBER_OF_ROLLS, {}, {}};
        eng.add_player(player);
    }
    ui->textEdit->clear();
    update_display();
}

