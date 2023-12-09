#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>




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
    std::string lineEditStdString = lineEditText.toStdString();
    this->close();

}


void MainWindow::on_Quit_clicked()
{
    this->close();
}

