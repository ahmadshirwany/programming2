#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <string>
using namespace std;

class Book
{
public:
    // Constructor
    Book(const string& title, const string& author, bool available = true);
    void print() const;
    void renew();
    void give_back();
    bool loan(const Date& day);

private:
    string title;
    string author;
    bool available;
    Date loan_date;
    Date due_date; // Added due date
};

#endif // BOOK_HH
