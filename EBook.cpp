#include "EBook.h"

#include <iomanip>
#include <sstream>

EBook::EBook(const std::string& t, const std::string& a, Genre g, double size)
    : Book(t, a, g), fileSizeMB(size) {}

void EBook::displayInfo() const {
    Book::displayInfo();
}

std::string EBook::getType() const {
    return "EBook";
}

std::string EBook::getExtraData() const {
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << fileSizeMB << " MB";
    return out.str();
}
