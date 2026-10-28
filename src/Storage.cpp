#include "Storage.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Storage::saveToFile(const std::string &filename, const std::vector<Transaction> &transactions)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open  file for writing" << std::endl;
        return;
    }

    for (auto &tx : transactions)
    {
        outFile << tx.getID() << "|" << tx.getType() << "|" << tx.getAmount() << "|" << tx.getCategory() << "|" << tx.getDescription() << "\n";
    }
    outFile.close();
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
        std::string idStr, type, amountStr, category, description;
        std::getline(ss, idStr, '|');
        std::getline(ss, type, '|');
        std::getline(ss, amountStr, '|');
        std::getline(ss, category, '|');
        std::getline(ss, description, '|');
        int id = std::stoi(idStr);
        double amount = std::stoi(amountStr);

        transactions.push_back(Transaction(id, type, amount, category, description));
    }
    inFile.close();
    return transactions;
}
