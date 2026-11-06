#pragma once
#include <string>
#include <vector>
#include "Transaction.h"
#include <map>
class Storage
{
public:
    static bool saveToFile(const std::string &filename, const std::vector<Transaction> &transactions);
    static std::vector<Transaction> loadFromFile(const std::string &filename);
    static bool saveBudgets(const std::string &filename, const std::map<std::string, double> &budgets);
    static std::map<std::string, double> loadBudgets(const std::string &filename);
};