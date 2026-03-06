#include "Date.h"

#include <ctime>
#include <iomanip>
#include <sstream>

std::string Date::now() {
    std::time_t current = std::time(nullptr);
    std::tm* local = std::localtime(&current);
    std::ostringstream out;
    out << std::put_time(local, "%Y-%m-%d %H:%M:%S");
    return out.str();
}
