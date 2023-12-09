#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "yatzy_game.hh"
#include "error.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Enter_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
    yatzy_game * Yatzy;
    error * Error_window;
};
#endif // MAINWINDOW_HH
