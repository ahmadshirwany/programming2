#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::on_countButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_closeButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked() {
    QString weightStr = ui->weightLineEdit->text();
    QString heightStr = ui->heightLineEdit->text();
    bool ok;
    double weight = weightStr.toDouble(&ok);
    if (!ok) {
        ui->resultLabel->setText("Invalid weight");
        return;
    }

    double height = heightStr.toDouble(&ok);
    if (!ok) {
        ui->resultLabel->setText("Invalid height");
        return;
    }
    double heightMeters = height / 100.0;
    double bmi = weight / (heightMeters * heightMeters);
    ui->resultLabel->setText(QString::number(bmi));
    if (bmi< 18.5){
         ui->infoTextBrowser->setText("Underweight");
    }
    else if(bmi< 25){
        ui->infoTextBrowser->setText("Overweight");
    }
    else{
         ui->infoTextBrowser->setText("Normal range");
    }

}

void MainWindow::on_closeButton_clicked()
{
     close();
}



