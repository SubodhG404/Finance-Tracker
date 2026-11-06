#include "Storage.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Storage::saveToFile(const std::string &filename, const std::vector<Transaction> &transactions)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open  file for writing" << std::endl;
        return false;
    }

    for (auto &tx : transactions)
    {
        outFile << tx.getID() << "|" << tx.getType() << "|" << tx.getAmount() << "|" << tx.getCategory() << "|" << tx.getDescription() << '|' << tx.getDate() << "\n";
    }
    outFile.close();
    return true;
}

std::vector<Transaction> Storage::loadFromFile(const std::string &filename)
{
    std::vector<Transaction> transactions;
    std::ifstream inFile(filename);

    if (!inFile.is_open())
    {
        return transactions;
    }
    std::string line;

    while (std::getline(inFile, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line); // reads string like an input stream
        std::string idStr, type, amountStr, category, description, date;
        std::getline(ss, idStr, '|');
        std::getline(ss, type, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, category, '|');
        std::getline(ss, description, '|');
        std::getline(ss, date, '|');
        int id = std::stoi(idStr);
        double amount = std::stod(amountStr);

        transactions.push_back(Transaction(id, type, amount, category, description, date));
    }
    inFile.close();
    return transactions;
}

bool Storage::saveBudgets(const std::string &filename, const std::map<std::string, double> &budgets)
{
    std::ofstream outfile(filename);

    if (!outfile.is_open())
    {
        std::cerr << "Failed to open  file for writing" << std::endl;
        return false;
    }

    for (auto &budget : budgets)
    {
        outfile << budget.first << "|" << budget.second << "\n";
    }

    outfile.close();
    return true;
}

std::map<std::string, double> Storage::loadBudgets(const std::string &filename)
{
    std::ifstream infile(filename);
    std::map<std::string, double> budgets;
    std::string line;

    if (!infile.is_open())
    {
        return budgets;
    }

    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;
        std::stringstream ss(line);
        std::string month, budgetStr;
        std::getline(ss, month, '|');
        std::getline(ss, budgetStr);
        budgets[month] = std::stod(budgetStr);
    }

    return budgets;
}