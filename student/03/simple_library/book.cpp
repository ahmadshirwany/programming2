// book.cpp
#include "book.hh"
#include <iostream>

// Constructor
Book::Book(const string& title, const string& author, bool available)
    : title(title), author(author), available(available) {}

// Print book information
void Book::print() const
{
    cout << title << " : " << author << endl;
    if (available)
    {
        cout << "- available" << endl;
    }
    else
    {
        cout << "- loaned: " ;
        loan_date.print();
        cout << "- to be returned: " ;
        due_date.print();
    }
}

// Renew the book
void Book::renew()
{
    if (available)
    {
        cout << "Not loaned: cannot be renewed" << endl;
    }
    else
    {  
        due_date.advance(28);

    }
}

// Give back the book
void Book::give_back()
{
    if (!available)
    {
        available = true;
    }
    else
    {
        cout << "Book is already available" << endl;
    }
}

// Loan the book
bool Book::loan(const Date& day)
{
    if (available)
    {
        available = false;
        loan_date = day;
        // Calculate the due date, which is 28 days from the loan date
        due_date = day;
        due_date.advance(28);
        return true;
    }
    else
    {
        cout << "Already loaned: cannot be loaned" << endl;
        return false;
    }
}
