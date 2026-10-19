#pragma once
#include <string>
class Transaction
{
private:
    int id;
    std::string type;
    double amount;
    std::string category;
    std::string description;

public:
    Transaction(int id, std::string type, double amount, std::string category, std::string description);

    void display() const;
};
