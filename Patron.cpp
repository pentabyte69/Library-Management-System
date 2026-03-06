#include "Patron.h"

#include "Book.h"

#include <algorithm>
#include <stdexcept>

Patron::Patron(const std::string& n, int i) : name(n), id(i) {}

void Patron::borrowBook(Book* b) {
    if (b == nullptr) {
        throw std::runtime_error("Cannot borrow a null book pointer.");
    }
    borrowedBooks.push_back(b);
}

void Patron::returnBook(Book* b) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), b);
    if (it == borrowedBooks.end()) {
        throw std::runtime_error("This patron did not borrow the selected book.");
    }
    borrowedBooks.erase(it);
}

void Patron::displayPatron() const {
    std::cout << *this << std::endl;
}

int Patron::getId() const {
    return id;
}

std::string Patron::getName() const {
    return name;
}

bool Patron::operator==(const Patron& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Patron& p) {
    os << "Patron ID: " << p.id << " | Name: " << p.name
       << " | Borrowed Books: " << p.borrowedBooks.size();
    return os;
}
