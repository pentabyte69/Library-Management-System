#include "Book.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::string normalize(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}
}

Book::Book(const std::string& t, const std::string& a, Genre g)
    : title(t), author(a), genre(g), status(BookStatus::Available) {}

void Book::displayInfo() const {
    std::cout << *this << std::endl;
}

void Book::setStatus(BookStatus s) {
    status = s;
}

BookStatus Book::getStatus() const {
    return status;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

Genre Book::getGenre() const {
    return genre;
}

bool Book::operator==(const Book& other) const {
    return title == other.title && author == other.author;
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
    os << "Title: " << b.title
       << " | Author: " << b.author
       << " | Genre: " << genreToString(b.genre)
       << " | Status: " << statusToString(b.status)
       << " | Type: " << b.getType()
       << " | Extra: " << b.getExtraData();
    return os;
}

std::string genreToString(Genre genre) {
    switch (genre) {
        case Genre::Fiction: return "Fiction";
        case Genre::NonFiction: return "NonFiction";
        case Genre::Mystery: return "Mystery";
        case Genre::Science: return "Science";
        case Genre::Biography: return "Biography";
        default: return "Unknown";
    }
}

Genre stringToGenre(const std::string& text) {
    std::string value = normalize(text);
    if (value == "fiction") return Genre::Fiction;
    if (value == "nonfiction" || value == "non-fiction") return Genre::NonFiction;
    if (value == "mystery") return Genre::Mystery;
    if (value == "science") return Genre::Science;
    if (value == "biography") return Genre::Biography;
    throw std::runtime_error("Invalid genre: " + text);
}

std::string statusToString(BookStatus status) {
    return status == BookStatus::Available ? "Available" : "CheckedOut";
}
