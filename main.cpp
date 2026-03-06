#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "EBook.h"
#include "Library.h"
#include "PrintedBook.h"

void showMenu() {
    std::cout << "\n===== Library Management System =====\n"
              << "1. Display all books\n"
              << "2. Display all patrons\n"
              << "3. Add printed book\n"
              << "4. Add ebook\n"
              << "5. Add patron\n"
              << "6. Check out book\n"
              << "7. Return book\n"
              << "8. Search by author\n"
              << "9. Search by genre\n"
              << "10. Display transactions\n"
              << "0. Save and exit\n"
              << "Enter choice: ";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Genre readGenre() {
    int choice;
    std::cout << "Select genre (1-Fiction, 2-NonFiction, 3-Mystery, 4-Science, 5-Biography): ";
    std::cin >> choice;
    if (std::cin.fail() || choice < 1 || choice > 5) {
        throw std::runtime_error("Invalid genre selection.");
    }
    return static_cast<Genre>(choice - 1);
}

int main() {
    Library library;

    try {
        library.loadData();
    } catch (const std::exception& e) {
        std::cerr << "Application Error: " << e.what() << std::endl;
        return 1;
    }

    int choice = -1;
    while (choice != 0) {
        try {
            showMenu();
            std::cin >> choice;
            if (std::cin.fail()) {
                throw std::runtime_error("Menu choice must be a number.");
            }
            clearInput();

            if (choice == 1) {
                library.displayBooks();
            } else if (choice == 2) {
                library.displayPatrons();
            } else if (choice == 3) {
                std::string title, author;
                int pages;
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                Genre genre = readGenre();
                clearInput();
                std::cout << "Enter page count: ";
                std::cin >> pages;
                if (std::cin.fail() || pages <= 0) {
                    throw std::runtime_error("Page count must be a positive integer.");
                }
                clearInput();
                library.addBook(new PrintedBook(title, author, genre, pages));
                std::cout << "Printed book added successfully.\n";
            } else if (choice == 4) {
                std::string title, author;
                double size;
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                Genre genre = readGenre();
                clearInput();
                std::cout << "Enter file size (MB): ";
                std::cin >> size;
                if (std::cin.fail() || size <= 0) {
                    throw std::runtime_error("File size must be a positive number.");
                }
                clearInput();
                library.addBook(new EBook(title, author, genre, size));
                std::cout << "EBook added successfully.\n";
            } else if (choice == 5) {
                std::string name;
                int id;
                std::cout << "Enter patron name: ";
                std::getline(std::cin, name);
                std::cout << "Enter patron ID: ";
                std::cin >> id;
                if (std::cin.fail() || id <= 0) {
                    throw std::runtime_error("Patron ID must be a positive integer.");
                }
                clearInput();
                library.addPatron(Patron(name, id));
                std::cout << "Patron added successfully.\n";
            } else if (choice == 6) {
                int patronId;
                std::string title;
                std::cout << "Enter patron ID: ";
                std::cin >> patronId;
                if (std::cin.fail()) {
                    throw std::runtime_error("Patron ID must be numeric.");
                }
                clearInput();
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                library.checkoutBook(patronId, title);
                std::cout << "Book checked out successfully.\n";
            } else if (choice == 7) {
                int patronId;
                std::string title;
                std::cout << "Enter patron ID: ";
                std::cin >> patronId;
                if (std::cin.fail()) {
                    throw std::runtime_error("Patron ID must be numeric.");
                }
                clearInput();
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                library.returnBook(patronId, title);
                std::cout << "Book returned successfully.\n";
            } else if (choice == 8) {
                std::string author;
                std::cout << "Enter author name: ";
                std::getline(std::cin, author);
                library.searchByAuthor(author);
            } else if (choice == 9) {
                Genre genre = readGenre();
                clearInput();
                library.searchByGenre(genre);
            } else if (choice == 10) {
                library.displayTransactions();
            } else if (choice == 0) {
                library.saveData();
                std::cout << "Data saved. Goodbye!\n";
            } else {
                std::cout << "Invalid menu option. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            clearInput();
        }
    }

    return 0;
}
