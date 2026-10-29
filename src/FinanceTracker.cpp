#include <iostream>
#include "FinanceTracker.h"
#include "Utils.h"
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

FinanceTracker::FinanceTracker(const std::string &storageFilename)
{
    transactions = Storage::loadFromFile(storageFilename);
    upadateNextId();
}

void FinanceTracker::upadateNextId()
{
    nextId = 1;
    for (const auto &tx : transactions)
    {
        if (tx.getID() >= nextId)
        {
            nextId = tx.getID() + 1;
        }
    }
}

void FinanceTracker::addTransaction(const std::string &description, double amount, const std::string &type, const std::string &category, const std::string &date)
{
    std::cout << "\nAdding Transaction......\n";

    Transaction newTx(nextId++, type, amount, category, description, date);
    transactions.push_back(newTx);

    std::cout << "\n Transaction Added Successfully";
}

void FinanceTracker::displayAllTransactions() const
{
    std::cout << "\nViewing Transactions......\n";
    if (transactions.empty())
    {
        std::cout << "No transactions Recorded yet\n";
    }

    else
    {
        for (const auto &tx : transactions)
        { // doesn't create copies, gives a refence
            tx.display();
            std::cout << "--------------------------------------------" << std::endl;
        }
    }
}

void FinanceTracker::displayTransactionsByMonth(const std::string &month) const
{
    bool found = false;
    std::cout << "\n--- Transactions for Month " << month << "---\n";
    if (transactions.empty())
    {
        std::cout << "No transactions Recorded yet\n";
    }

    else
    {
        for (const auto &tx : transactions)
        {
            // compare YYYY-MM part for YYYY-MM-DD
            if (tx.getDate().length() >= 7 && tx.getDate().substr() == month)
            {
                tx.display();
                found = true;
            }
        }

        if (!found)
        {
            std::cout << " No Transactions for the Month " << month << "\n";
        }
        std::cout << "--------------------------------------------";
    }
}

void FinanceTracker::calculateSummary() const
{

    double income = 0;
    double expense = 0;

    for (const Transaction &t : transactions)
    {
        if (t.getType() == "Income")
        {
            income += t.getAmount();
        }
        else if (t.getType() == "Expense")
        {
            expense += t.getAmount();
        }
    }

    std::ostringstream incStr, expStr, netStr;
    incStr << std::fixed << std::setprecision(2) << income;
    expStr << std::fixed << std::setprecision(2) << expense;
    netStr << std::fixed << std::setprecision(2) << (income - expense);

    printCentered("----------Monthly Summary----------\n");
    printCentered("Total Income  : Rs. " + incStr.str() + "\n");
    printCentered("Total Expense : Rs. " + expStr.str() + "\n");
    printCentered("Net Balance   : Rs. " + netStr.str() + "\n");
    printCentered("--------------------------------------------");
}

void FinanceTracker::calculateMonthlySummary(const std::string &month) const
{
    double income = 0;
    double expense = 0;

    for (const Transaction &t : transactions)
    {
        if (t.getDate().length() >= 7 && t.getDate().substr() == month)
        {
            if (t.getType() == "Income")
            {
                income += t.getAmount();
            }
            else if (t.getType() == "Expense")
            {
                expense += t.getAmount();
            }
        }
    }

    std::ostringstream incStr, expStr, netStr;
    incStr << std::fixed << std::setprecision(2) << income;
    expStr << std::fixed << std::setprecision(2) << expense;
    netStr << std::fixed << std::setprecision(2) << (income - expense);

    printCentered("----------Monthly Summary----------\n");
    printCentered("Total Income  : Rs. " + incStr.str() + "\n");
    printCentered("Total Expense : Rs. " + expStr.str() + "\n");
    printCentered("Net Balance   : Rs. " + netStr.str() + "\n");
    printCentered("--------------------------------------------");
}
bool FinanceTracker::saveTransactions() const
{
    Storage::saveToFile("transactions.txt", transactions);
}