#ifndef EBOOK_H
#define EBOOK_H

#include "Book.h"

// Represents a digital book with a file size.
class EBook : public Book {
private:
    double fileSizeMB;

public:
    EBook(const std::string& t, const std::string& a, Genre g, double size);
    void displayInfo() const override;
    std::string getType() const override;
    std::string getExtraData() const override;
};

#endif
