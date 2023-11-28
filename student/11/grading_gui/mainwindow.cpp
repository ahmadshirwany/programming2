#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"
#include "string"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxN->setMinimum(0);
    ui->spinBoxG->setMinimum(0);
    ui->spinBoxP->setMinimum(0);
    ui->spinBoxE->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);
    ui->spinBoxE->setMaximum(5);
    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::on_calculatePushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculatePushButton_clicked()
{
    unsigned int N_points = ui->spinBoxN->value();
    unsigned int G_points = ui->spinBoxG->value();
    unsigned int P_points = ui->spinBoxP->value();
    unsigned int E_points = ui->spinBoxE->value();
    int total_grade = calculate_total_grade(N_points,G_points,P_points,E_points);
    int score_weekly_exercises = score_from_weekly_exercises(N_points,G_points);
    int score_projects = score_from_projects(P_points);
    QString Text = "W-Score: " + QString::number(score_weekly_exercises) +
                   "\nP-Score: " + QString::number(score_projects) +
                   "\nTotal grade: " + QString::number(total_grade);
    ui->textBrowser->setText(Text);

}

