#pragma once
#include <vector>
#include <string>
#include "Transaction.h"
#include "Storage.h"

class FinanceTracker
{
private:
    std::vector<Transaction> transactions;
    std::string filename;
    int nextId;

    void upadateNextId();

public:
    explicit FinanceTracker(const std::string &storageFilename = "transactions.txt");

    // Core Business Logic Methods
    void addTransaction(const std::string &description, double amount, const std::string &type, const std::string &category, const std::string &date);
    void displayAllTransactions() const;
    void calculateSummary() const;

    // Persistence Methods
    bool saveTransactions() const;

    // Getter for transactions (useful for future features like filtering/searching)
    const std::vector<Transaction> &getTransactions() const;

    void displayTransactionsByMonth(const std::string &month) const;
    void calculateMonthlySummary(const std::string &month) const;
};