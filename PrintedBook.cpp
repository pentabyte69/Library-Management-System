#include "PrintedBook.h"

#include <sstream>

PrintedBook::PrintedBook(const std::string& t, const std::string& a, Genre g, int pages)
    : Book(t, a, g), pageCount(pages) {}

void PrintedBook::displayInfo() const {
    Book::displayInfo();
}

std::string PrintedBook::getType() const {
    return "PrintedBook";
}

std::string PrintedBook::getExtraData() const {
    return std::to_string(pageCount) + " pages";
}

