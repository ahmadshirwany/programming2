#include "error.hh"
#include "ui_error.h"
#include <string>

error::error(QWidget *parent, std::string error_msg) :
    QDialog(parent),
    ui(new Ui::error)
{
    ui->setupUi(this);
}

error::~error()
{
    delete ui;
}
