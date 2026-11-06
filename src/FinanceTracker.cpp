#include <iostream>
#include "FinanceTracker.h"
#include "Storage.h"
#include "Utils.h"
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
FinanceTracker::FinanceTracker(const std::string &storageFilename, const std::string &budgetsStorageFilename) : filename(storageFilename), budgetsFilename(budgetsStorageFilename), nextId(1)
{
    transactions = Storage::loadFromFile(filename);
    monthlyBudget = Storage::loadBudgets(budgetsFilename);
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
            if (tx.getDate().length() >= 7 && tx.getDate().substr(0, 7) == month)
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
bool FinanceTracker::containsIgnoreCase(const std::string &text, const std::string &query) const
{
    std::string textLower = text;
    std::string queryLower = query;

    std::transform(textLower.begin(), textLower.end(), textLower.begin(), ::tolower);
    std::transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

    return textLower.find(queryLower) != std::string::npos;
}

void FinanceTracker::searchTransactions(const std::string &query) const
{
    std::cout << "Search Results for Query: " << query << "\n";
    bool found = false;

    for (const auto &t : transactions)
    {
        if (containsIgnoreCase(t.getCategory(), query) || containsIgnoreCase(t.getDescription(), query))
        {
            t.display();
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "Query Results not found!\n";
    }
}

void FinanceTracker::setBudget(const std::string &month, double amount)
{
    if (amount < 0)
    {
        std::cout << "Budget is invalid. I must be non-negative!" << std::endl;
        return;
    }

    monthlyBudget[month] = amount;
    std::cout << "Budget of $" << std::fixed << std::setprecision(2) << amount << " set for " << month << "Successfully!" << std::endl;
}

void FinanceTracker::checkBudget(const std::string &month) const
{
    auto it = monthlyBudget.find(month);
    if (it == monthlyBudget.end())
    {
        std::cout << "No budget set for month " << month << std::endl;
        return;
    }
    double budgetLimit = it->second;
    double totalExpense = 0;
    for (auto &tx : transactions)
    {
        if (tx.getDate().substr(0, 7) == month && tx.getType() == "Expense")
        {
            totalExpense += tx.getAmount();
        }
    }

    double remaining = budgetLimit - totalExpense;

    if (remaining < 0)
    {
        std::cout << "You've already spended more than your budget!\n Extra Money Spent" << -remaining << "\n";
    }
    else if (budgetLimit > 0 && totalExpense / budgetLimit >= 0.80)
    {
        std::cout << "Alert : You are nearing your budget \n Spended : " << totalExpense << " Budget : " << budgetLimit << "Remaining : " << remaining << "\n";
    }
    else
    {
        std::cout << "Spended : " << totalExpense << " Budget : " << budgetLimit << "Remaining : " << remaining << "\n";
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
        if (t.getDate().length() >= 7 && t.getDate().substr(0, 7) == month)
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
    return Storage::saveToFile(filename, transactions);
}
bool FinanceTracker::saveMonthlyBudgets() const
{
    return Storage::saveBudgets(budgetsFilename, monthlyBudget);
}
