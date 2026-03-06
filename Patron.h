#ifndef PATRON_H
#define PATRON_H

#include <iostream>
#include <string>
#include <vector>

class Book;

// Represents a library user who can borrow books.
class Patron {
private:
    std::string name;
    int id;
    std::vector<Book*> borrowedBooks;

public:
    Patron(const std::string& n = "", int i = 0);

    void borrowBook(Book* b);
    void returnBook(Book* b);
    void displayPatron() const;
    int getId() const;
    std::string getName() const;

    bool operator==(const Patron& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Patron& p);
};

#endif

