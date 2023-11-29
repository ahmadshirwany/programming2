#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetButtonClicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closeButtonClicked);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
    }

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::startButtonClicked()
{
   timer->start(1000);
}

void MainWindow::stopButtonClicked()
{
    if (timer!=nullptr)
        {
            timer->stop();

        }
}

void MainWindow::resetButtonClicked()
{
    // Reset the timer to zero
    currentMinutes = 0;
    currentSeconds = 0;
    updateTimerDisplay();
}

void MainWindow::closeButtonClicked()
{
    // Close the window
    close();
}

void MainWindow::updateTimerDisplay()
{
    // Update the current time on the display
    currentSeconds++;
    if (currentSeconds == 60) {
        currentSeconds = 0;
        currentMinutes++;
    }

    ui->lcdNumberSec->display(currentSeconds);
    ui->lcdNumberMin->display(currentMinutes);
}
