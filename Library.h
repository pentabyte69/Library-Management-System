#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"

// Main coordinator class for the whole application.
class Library {
private:
    std::vector<Book*> books;
    std::vector<Patron> patrons;
    std::vector<Transaction> transactions;
    std::map<int, std::string> patronDirectory;

    Book* findBookByTitle(const std::string& title) const;
    Patron* findPatronById(int patronId);
    const Patron* findPatronById(int patronId) const;

    template <typename Collection>
    void saveLines(const std::string& fileName, const Collection& lines) const {
        std::ofstream outFile(fileName);
        if (!outFile) {
            throw std::runtime_error("Failed to save file: " + fileName);
        }
        for (const auto& line : lines) {
            outFile << line << '\n';
        }
    }

public:
    ~Library();

    void loadData();
    void saveData() const;
    void addBook(Book* b);
    void addPatron(const Patron& p);
    void checkoutBook(int patronId, const std::string& title);
    void returnBook(int patronId, const std::string& title);
    void displayBooks() const;
    void displayPatrons() const;
    void displayTransactions() const;
    void searchByAuthor(const std::string& author) const;
    void searchByGenre(Genre genre) const;
};

#endif
