#include "Library.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "Date.h"
#include "EBook.h"
#include "PrintedBook.h"

namespace {
std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
        parts.push_back(item);
    }
    return parts;
}
}

Library::~Library() {
    for (Book* book : books) {
        delete book;
    }
}

Book* Library::findBookByTitle(const std::string& title) const {
    for (Book* book : books) {
        if (book->getTitle() == title) {
            return book;
        }
    }
    return nullptr;
}

Patron* Library::findPatronById(int patronId) {
    for (Patron& patron : patrons) {
        if (patron.getId() == patronId) {
            return &patron;
        }
    }
    return nullptr;
}

const Patron* Library::findPatronById(int patronId) const {
    for (const Patron& patron : patrons) {
        if (patron.getId() == patronId) {
            return &patron;
        }
    }
    return nullptr;
}

void Library::loadData() {
    std::ifstream booksFile("books.txt");
    if (!booksFile) {
        throw std::runtime_error("Failed to open books.txt");
    }

    std::string line;
    while (std::getline(booksFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> parts = splitCSV(line);
        if (parts.size() != 5) {
            throw std::runtime_error("Invalid book record: " + line);
        }

        Genre genre = stringToGenre(parts[0]);
        const std::string& title = parts[1];
        const std::string& author = parts[2];
        const std::string& type = parts[3];
        const std::string& extra = parts[4];

        if (type == "Printed") {
            addBook(new PrintedBook(title, author, genre, std::stoi(extra)));
        } else if (type == "EBook") {
            addBook(new EBook(title, author, genre, std::stod(extra)));
        } else {
            throw std::runtime_error("Unknown book type: " + type);
        }
    }

    std::ifstream patronsFile("patrons.txt");
    if (!patronsFile) {
        throw std::runtime_error("Failed to open patrons.txt");
    }

    while (std::getline(patronsFile, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> parts = splitCSV(line);
        if (parts.size() != 2) {
            throw std::runtime_error("Invalid patron record: " + line);
        }
        addPatron(Patron(parts[1], std::stoi(parts[0])));
    }
}

void Library::saveData() const {
    std::vector<std::string> patronLines;
    for (const Patron& patron : patrons) {
        patronLines.push_back(std::to_string(patron.getId()) + "," + patron.getName());
    }
    saveLines("patrons_saved.txt", patronLines);

    std::vector<std::string> transactionLines;
    for (const Transaction& tx : transactions) {
        transactionLines.push_back(tx.toCSV());
    }
    saveLines("transactions.txt", transactionLines);
}

void Library::addBook(Book* b) {
    if (b == nullptr) {
        throw std::runtime_error("Cannot add a null book.");
    }
    books.push_back(b);
}

void Library::addPatron(const Patron& p) {
    if (findPatronById(p.getId()) != nullptr) {
        throw std::runtime_error("Patron ID already exists.");
    }
    patrons.push_back(p);
    patronDirectory[p.getId()] = p.getName();
}

void Library::checkoutBook(int patronId, const std::string& title) {
    Patron* patron = findPatronById(patronId);
    if (patron == nullptr) {
        throw std::runtime_error("Invalid patron ID.");
    }

    Book* book = findBookByTitle(title);
    if (book == nullptr) {
        throw std::runtime_error("Book not found.");
    }
    if (book->getStatus() == BookStatus::CheckedOut) {
        throw std::runtime_error("Book is already checked out.");
    }

    patron->borrowBook(book);
    book->setStatus(BookStatus::CheckedOut);
    transactions.push_back(Transaction(patronId, patron->getName(), title, "Checked Out", Date::now()));
}

void Library::returnBook(int patronId, const std::string& title) {
    Patron* patron = findPatronById(patronId);
    if (patron == nullptr) {
        throw std::runtime_error("Invalid patron ID.");
    }

    Book* book = findBookByTitle(title);
    if (book == nullptr) {
        throw std::runtime_error("Book not found.");
    }

    patron->returnBook(book);
    book->setStatus(BookStatus::Available);
    transactions.push_back(Transaction(patronId, patron->getName(), title, "Returned", Date::now()));
}

void Library::displayBooks() const {
    std::cout << "\n--- Library Books ---\n";
    for (const Book* book : books) {
        book->displayInfo();
    }
}

void Library::displayPatrons() const {
    std::cout << "\n--- Patrons ---\n";
    for (const Patron& patron : patrons) {
        patron.displayPatron();
    }
}

void Library::displayTransactions() const {
    std::cout << "\n--- Transactions ---\n";
    for (const Transaction& tx : transactions) {
        tx.displayTransaction();
    }
}

void Library::searchByAuthor(const std::string& author) const {
    std::cout << "\nSearch results for author: " << author << '\n';
    bool found = false;
    for (const Book* book : books) {
        if (book->getAuthor() == author) {
            book->displayInfo();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found for that author." << std::endl;
    }
}

void Library::searchByGenre(Genre genre) const {
    std::cout << "\nSearch results for genre: " << genreToString(genre) << '\n';
    bool found = false;
    for (const Book* book : books) {
        if (book->getGenre() == genre) {
            book->displayInfo();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No books found in that genre." << std::endl;
    }
}

