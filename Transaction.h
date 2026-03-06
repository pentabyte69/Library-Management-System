#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>

// Stores a checkout or return action for logging purposes.
class Transaction {
private:
    int patronId;
    std::string patronName;
    std::string bookTitle;
    std::string action;
    std::string date;

public:
    Transaction(int pid, const std::string& pName, const std::string& bt,
                const std::string& actionTaken, const std::string& dateStamp);
    void displayTransaction() const;
    std::string toCSV() const;
};

#endif

