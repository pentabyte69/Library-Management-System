#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

// Genre categories supported by the library.
enum class Genre { Fiction, NonFiction, Mystery, Science, Biography };

// Availability state for each book.
enum class BookStatus { Available, CheckedOut };

// Base class representing a general book in the library.
class Book {
protected:
    std::string title;
    std::string author;
    Genre genre;
    BookStatus status;

public:
    Book(const std::string& t, const std::string& a, Genre g);
    virtual ~Book() = default;

    virtual void displayInfo() const;
    virtual std::string getType() const = 0;
    virtual std::string getExtraData() const = 0;

    void setStatus(BookStatus s);
    BookStatus getStatus() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    Genre getGenre() const;

    bool operator==(const Book& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Book& b);
};

std::string genreToString(Genre genre);
Genre stringToGenre(const std::string& text);
std::string statusToString(BookStatus status);

#endif
