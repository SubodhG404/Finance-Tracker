#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

class Storage
{
public:
    static bool saveToFile(const std::string &filename, const std::vector<Transaction> &transactions);
    static std::vector<Transaction> loadFromFile(const std::string &filename);
};