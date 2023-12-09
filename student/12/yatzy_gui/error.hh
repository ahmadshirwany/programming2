#ifndef ERROR_HH
#define ERROR_HH

#include <QDialog>
#include <string>

namespace Ui {
class error;
}

class error : public QDialog
{
    Q_OBJECT

public:
    explicit error(QWidget *parent = nullptr, std::string error_msg = "");
    ~error();

private:
    Ui::error *ui;
};

#endif // ERROR_HH
