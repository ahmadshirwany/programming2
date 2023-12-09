#include "error.hh"
#include "ui_error.h"
#include <string>

error::error(QWidget *parent, QString error_msg) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
    ui->label->setText(error_msg);
}

error::~error()
{
    delete ui;
}
