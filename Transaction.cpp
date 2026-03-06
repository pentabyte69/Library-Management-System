#include "Transaction.h"

Transaction::Transaction(int pid, const std::string& pName, const std::string& bt,
                         const std::string& actionTaken, const std::string& dateStamp)
    : patronId(pid), patronName(pName), bookTitle(bt), action(actionTaken), date(dateStamp) {}

void Transaction::displayTransaction() const {
    std::cout << "Date: " << date
              << " | Patron ID: " << patronId
              << " | Patron: " << patronName
              << " | Action: " << action
              << " | Book: " << bookTitle << std::endl;
}

std::string Transaction::toCSV() const {
    return std::to_string(patronId) + "," + patronName + "," + action + "," + bookTitle + "," + date;
}

