#include "Storage.h"
#include <iostream>
#include <fstream>
static void saveToFile(const std::string &filename, const std::vector<Transaction> &transactions)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open  file" << std::endl;
        return;
    }

    for (auto &tx : transactions)
    {
        outFile << tx.getID() << "|" << tx.getType() << "|" << tx.getAmount() << "|" << tx.getCategory() << "|" << tx.getDescription() << "\n";
    }
    outFile.close();
}

static std::vector<Transaction> loadFromFile(const std::string &filename)
{
    std::vector<Transaction> transactions;
    std::ifstream inFile(filename);
}
