#ifndef PRINTEDBOOK_H
#define PRINTEDBOOK_H

#include "Book.h"

// Represents a physical printed book with a page count.
class PrintedBook : public Book {
private:
    int pageCount;

public:
    PrintedBook(const std::string& t, const std::string& a, Genre g, int pages);
    void displayInfo() const override;
    std::string getType() const override;
    std::string getExtraData() const override;
};

#endif

