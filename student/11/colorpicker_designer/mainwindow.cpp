#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSliderRed->setMinimum(0);
    ui->horizontalSliderRed->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreen->setMinimum(0);
    ui->horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlue->setMinimum(0);
    ui->horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);

    ui->spinBoxRed->setMinimum(0);
    ui->spinBoxGreen->setMinimum(0);
    ui->spinBoxBlue->setMinimum(0);
    ui->spinBoxRed->setMaximum(RGB_VALUE_MAX);
    ui->spinBoxGreen->setMaximum(RGB_VALUE_MAX);
    ui->spinBoxBlue->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &MainWindow::onColorChanged);

    connect(ui->spinBoxRed, &QSpinBox::valueChanged, this, &MainWindow::spinboxvaluechange);
    connect(ui->spinBoxGreen, &QSpinBox::valueChanged, this, &MainWindow::spinboxvaluechange);
    connect(ui->spinBoxBlue, &QSpinBox::valueChanged, this, &MainWindow::spinboxvaluechange);

    onColorChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorChanged()
{
    //qDebug() << "onColorChanged";
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());

    ui->spinBoxRed->setValue(ui->horizontalSliderRed->value());
    ui->spinBoxBlue->setValue(ui->horizontalSliderBlue->value());
    ui->spinBoxGreen->setValue(ui->horizontalSliderGreen->value());
    QPixmap colorMap(64, 64);
    colorMap.fill(selectedColor);
    ui->colorLabel->setPixmap(colorMap);
}

void MainWindow::spinboxvaluechange()
{
    ui->horizontalSliderRed->setValue(ui->spinBoxRed->value());
    ui->horizontalSliderGreen->setValue(ui->spinBoxGreen->value());
    ui->horizontalSliderBlue->setValue(ui->spinBoxBlue->value());
}


