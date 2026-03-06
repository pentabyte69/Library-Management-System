#ifndef DATE_H
#define DATE_H

#include <string>

// Small helper class used to stamp transaction dates.
class Date {
public:
    static std::string now();
};

#endif
