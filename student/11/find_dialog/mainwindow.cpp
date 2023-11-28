#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->fileLineEdit, SIGNAL(editingFinished()), this, SLOT(on_fileLineEdit_editingFinished()));
    connect(ui->keyLineEdit, SIGNAL(editingFinished()), this, SLOT(on_keyLineEdit_editingFinished()));
    connect(ui->findPushButton, SIGNAL(clicked()), this, SLOT(on_findPushButton_clicked()));
    connect(ui->closePushButton, SIGNAL(clicked()), this, SLOT(on_closePushButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    filePath = ui->fileLineEdit->text();
}
void MainWindow::on_keyLineEdit_editingFinished() {
     key = ui->keyLineEdit->text();
}
void MainWindow::on_findPushButton_clicked() {
    bool caseSensitive =  ui->matchCheckBox->isChecked();
    std::string filename =  filePath.toStdString();
    std::string searchKey = key.toStdString();
    std::ifstream file(filename);
        if (!file.is_open()) {
            ui->textBrowser->setText("File not found");
             return;
        }
        if (searchKey=="") {
            ui->textBrowser->setText("File found");
             return;
        }
        std::string line;
        bool keyFound = false;
        while (std::getline(file, line)) {
            if (!caseSensitive) {
                        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
                        std::string lowercaseSearchKey = searchKey;
                        std::transform(lowercaseSearchKey.begin(), lowercaseSearchKey.end(), lowercaseSearchKey.begin(), ::tolower);
                        if (line.find(lowercaseSearchKey) != std::string::npos) {
                            keyFound = true;
                            file.close();
                            break;
                        }
                    } else {
                        if (line.find(searchKey) != std::string::npos) {
                               keyFound = true;
                                file.close();
                               break;
                        }
                    }
                }


        if (keyFound) {
            ui->textBrowser->setText("Word found");
        } else {
              ui->textBrowser->setText("Word not found");
        }

        return ;
}

void MainWindow::on_closePushButton_clicked()
{
     close();
}


